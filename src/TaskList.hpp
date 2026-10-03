#ifndef TASK_LIST_HPP
#define TASK_LIST_HPP

#include "Task.hpp"
//#include "PriorityTask.hpp"
//#include "TaskWithDate.hpp"

#include <memory>
#include <string>
#include <vector>

/**
 * @brief In-memory collection of tasks with create, read, update and delete support.
 */
class TaskList {
private:
    std::vector<std::unique_ptr<Task>> tasks;

    bool isValidIndex(int index) const;

public:
    void addTask(const std::string& title, const std::string& description, TaskStatus status);
//    void addPriorityTask(const std::string& title, const std::string& description, TaskStatus status, TaskPriority priority);
//    void addTaskWithDate(const std::string& title, const std::string& description, TaskStatus status, ...);

    bool updateTaskTitle(int index, const std::string& title);
    bool updateTaskDescription(int index, const std::string& description);
    bool updateTaskStatus(int index, TaskStatus status);
    bool deleteTask(int index);

    bool isEmpty() const;
    int getTaskCount() const;
    const std::vector<std::unique_ptr<Task>>& getTasks() const;
};

#endif