#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include "Task.hpp"
#include "TaskList.hpp"

#include <QSqlDatabase>
#include <QString>

class DatabaseManager {
private:
    QSqlDatabase db;
    QString connectionName;

public:
    explicit DatabaseManager(const QString& dbPath = "tasks.db",
                             const QString& connName = "ToDoConnection");
    ~DatabaseManager();

    bool connect();
    void disconnect();
    bool isOpen() const;

    bool createTable();
    bool loadTasks(TaskList& taskList) const;

    /**
     * @brief Inserts a new task of any type and stores the new id inside it (Daniel).
     *
     * @param task Task to save; after the call task.getId() returns its row id.
     * @return True when the task was saved; on failure lastError() explains why.
     */
    bool saveTask(Task& task);

    /**
     * @brief Changes the status of a saved task (Daniel).
     *
     * @param taskId Row id of the task (Task::getId()).
     * @param status New status.
     * @return True when a row with that id was updated.
     */
    bool updateStatus(int taskId, TaskStatus status);

    /**
     * @brief Overload: saves the current status of a task already in the database (Daniel).
     *
     * @param task Task whose getId() and getStatus() are used.
     * @return True when a row with that id was updated.
     */
    bool updateStatus(const Task& task);

    /**
     * @brief Deletes a saved task (Daniel).
     *
     * @param taskId Row id of the task (Task::getId()).
     * @return True when a row with that id was deleted.
     */
    bool deleteTask(int taskId);

    QString lastError() const;
};

#endif  // DATABASE_MANAGER_HPP
