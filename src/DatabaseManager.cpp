#include "DatabaseManager.hpp"

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
    }

    return query.lastError().type() == QSqlError::NoError;
}

QString DatabaseManager::lastError() const {
    return db.lastError().text();
}