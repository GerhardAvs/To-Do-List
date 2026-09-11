#ifndef TASK_LIST_HPP
#define TASK_LIST_HPP

#include "Task.hpp"

#include <vector>

class TaskList {
private:
    std::vector<Task> tasks;

public:
    void addTask(const std::string& description, TaskStatus status);
    bool updateTaskStatus(int position, TaskStatus status);
    bool deleteTask(int position);

    int getTaskCount() const;
    const std::vector<Task>& getTasks() const;
};

#endif
