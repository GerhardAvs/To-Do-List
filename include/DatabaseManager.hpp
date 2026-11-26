#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

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

    QString lastError() const;
};

#endif  // DATABASE_MANAGER_HPP