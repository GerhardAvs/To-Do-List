#include "DatabaseManager.hpp"

#include "PriorityTask.hpp"
#include "TaskWithDate.hpp"

#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

using namespace std;

namespace {

TaskStatus statusFromDbValue(int dbStatus) {
    switch (dbStatus) {
        case 1:
            return TaskStatus::InProgress;
        case 2:
            return TaskStatus::Completed;
        case 0:
        default:
            return TaskStatus::Pending;
    }
}

/**
 * @brief Converts a TaskStatus into the number stored in the completed column.
 *
 * Inverse of statusFromDbValue(): 0 Pending, 1 In progress, 2 Completed.
 *
 * @param status Status to convert.
 * @return Value for the completed column.
 */
int statusToDbValue(TaskStatus status) {
    switch (status) {
        case TaskStatus::InProgress:
            return 1;
        case TaskStatus::Completed:
            return 2;
        case TaskStatus::Pending:
        default:
            return 0;
    }
}

TaskPriority priorityFromDbValue(int dbPriority) {
    switch (dbPriority) {
        case static_cast<int>(TaskPriority::Low):
            return TaskPriority::Low;
        case static_cast<int>(TaskPriority::High):
            return TaskPriority::High;
        case static_cast<int>(TaskPriority::Medium):
        default:
            return TaskPriority::Medium;
    }
}

bool parseIsoDate(const QString& dateStr, int& day, int& month, int& year) {
    const QStringList parts = dateStr.split('-');
    if (parts.size() != 3) {
        return false;
    }

    bool okYear = false;
    bool okMonth = false;
    bool okDay = false;

    year = parts[0].toInt(&okYear);
    month = parts[1].toInt(&okMonth);
    day = parts[2].toInt(&okDay);

    if (!okYear || !okMonth || !okDay) {
        return false;
    }

    return isValidDate(day, month, year);
}

}  // namespace

DatabaseManager::DatabaseManager(const QString& dbPath, const QString& connName)
    : connectionName(connName) {
    if (QSqlDatabase::contains(connectionName)) {
        db = QSqlDatabase::database(connectionName);
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    }
    db.setDatabaseName(dbPath);
}

DatabaseManager::~DatabaseManager() {
    disconnect();
}

bool DatabaseManager::connect() {
    if (db.isOpen()) {
        return true;
    }
    return db.open();
}

void DatabaseManager::disconnect() {
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseManager::isOpen() const {
    return db.isOpen();
}

bool DatabaseManager::createTable() {
    if (!db.isOpen() && !connect()) {
        return false;
    }

    QSqlQuery query(db);
    const QString sql = R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            type TEXT NOT NULL,
            title TEXT NOT NULL,
            description TEXT,
            completed INTEGER DEFAULT 0,
            due_date TEXT,
            priority INTEGER
        );
    )";

    return query.exec(sql);
}

bool DatabaseManager::loadTasks(TaskList& taskList) const {
    if (!db.isOpen()) {
        return false;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT id, type, title, description, completed, due_date, priority FROM tasks ORDER BY id ASC")) {
        return false;
    }

    while (query.next()) {
        const QString type = query.value(1).toString().trimmed();
        const string title = query.value(2).toString().toStdString();
        const string description = query.value(3).toString().toStdString();
        const TaskStatus status = statusFromDbValue(query.value(4).toInt());

        if (type.compare("Priority", Qt::CaseInsensitive) == 0) {
            const TaskPriority priority = priorityFromDbValue(query.value(6).toInt());
            taskList.addTask(title, description, status, priority);
        } else if (type.compare("WithDate", Qt::CaseInsensitive) == 0 ||
                   type.compare("With due date", Qt::CaseInsensitive) == 0) {
            int day = 1;
            int month = 1;
            int year = minYear;
            const QString dueDate = query.value(5).toString().trimmed();

            if (parseIsoDate(dueDate, day, month, year)) {
                taskList.addTask(title, description, status, day, month, year);
            } else {
                taskList.addTask(title, description, status);
            }
        } else {
            taskList.addTask(title, description, status);
        }

        // Keep the row id so updateStatus() and deleteTask() can find the task later.
        taskList.getTasks().back()->setId(query.value(0).toInt());
    }

    return query.lastError().type() == QSqlError::NoError;
}

QString DatabaseManager::lastError() const {
    return db.lastError().text();
}

// =====================================================================
// Daniel: saveTask(), updateStatus() and deleteTask().
// Every query uses prepare() + bindValue(), never text concatenation.
// =====================================================================

/**
 * @brief Inserts a new task of any type and stores the new id inside it.
 *
 * The type column gets getTypeName() ("Normal", "Priority" or "With due date"),
 * the same names loadTasks() recognizes. Priority and due date are saved only
 * for the types that have them; the others store NULL. This is the database
 * layer, so checking the real type with dynamic_cast is allowed here.
 *
 * @param task Task to save; after the call task.getId() returns its row id.
 * @return True when the task was saved; on failure lastError() explains why.
 */
bool DatabaseManager::saveTask(Task& task) {
    if (!db.isOpen()) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO tasks (type, title, description, completed, due_date, priority) "
        "VALUES (:type, :title, :description, :completed, :due_date, :priority)");

    QVariant dueDate(QMetaType::fromType<QString>());   // NULL by default
    QVariant priority(QMetaType::fromType<int>());      // NULL by default

    if (const auto* dateTask = dynamic_cast<const TaskWithDate*>(&task)) {
        dueDate = QString::fromStdString(dateTask->getDate());
    }

    if (const auto* priorityTask = dynamic_cast<const PriorityTask*>(&task)) {
        priority = static_cast<int>(priorityTask->getPriority());
    }

    query.bindValue(":type", QString::fromStdString(task.getTypeName()));
    query.bindValue(":title", QString::fromStdString(task.getTitle()));
    query.bindValue(":description", QString::fromStdString(task.getDescription()));
    query.bindValue(":completed", statusToDbValue(task.getStatus()));
    query.bindValue(":due_date", dueDate);
    query.bindValue(":priority", priority);

    if (!query.exec()) {
        return false;
    }

    task.setId(query.lastInsertId().toInt());
    return true;
}

/**
 * @brief Changes the status of a saved task.
 *
 * @param taskId Row id of the task (Task::getId()).
 * @param status New status.
 * @return True when a row with that id was updated.
 */
bool DatabaseManager::updateStatus(int taskId, TaskStatus status) {
    if (!db.isOpen()) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE tasks SET completed = :completed WHERE id = :id");
    query.bindValue(":completed", statusToDbValue(status));
    query.bindValue(":id", taskId);

    return query.exec() && query.numRowsAffected() > 0;
}

/**
 * @brief Overload: saves the current status of a task already in the database.
 *
 * @param task Task whose getId() and getStatus() are used.
 * @return True when a row with that id was updated.
 */
bool DatabaseManager::updateStatus(const Task& task) {
    return updateStatus(task.getId(), task.getStatus());
}

/**
 * @brief Deletes a saved task.
 *
 * @param taskId Row id of the task (Task::getId()).
 * @return True when a row with that id was deleted.
 */
bool DatabaseManager::deleteTask(int taskId) {
    if (!db.isOpen()) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM tasks WHERE id = :id");
    query.bindValue(":id", taskId);

    return query.exec() && query.numRowsAffected() > 0;
}
