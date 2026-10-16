#ifndef TASK_LIST_HPP
#define TASK_LIST_HPP

#include "Task.hpp"
#include "PriorityTask.hpp"
#include "TaskWithDate.hpp"

#include <memory>
#include <string>
#include <vector>

/**
 * @brief Manages a collection of tasks stored as polymorphic unique pointers.
 */
class TaskList {
private:
    std::vector<std::unique_ptr<Task>> tasks;

    bool isValidIndex(int index) const;

public:
    TaskList() = default;

    /**
     * @brief Creates a standard task and stores it at the end of the list.
     *
     * @param title Short name of the task.
     * @param description Detailed text explaining the task.
     * @param status Initial progress state of the task.
     */
    void addTask(const std::string& title, const std::string& description, TaskStatus status);

    /**
     * @brief Creates a PriorityTask and stores it at the end of the list.
     *
     * @param title Short name of the task.
     * @param description Detailed text explaining the task.
     * @param status Initial progress state of the task.
     * @param priority Priority level of the task.
     */
    void addPriorityTask(const std::string& title, const std::string& description, TaskStatus status, TaskPriority priority);

    /**
     * @brief Creates a TaskWithDate and stores it at the end of the list.
     *
     * @param title Short name of the task.
     * @param description Detailed text explaining the task.
     * @param status Initial progress state of the task.
     * @param day Day of the target due date.
     * @param month Month of the target due date.
     * @param year Year of the target due date.
     */
    void addTaskWithDate(const std::string& title, const std::string& description, TaskStatus status, int day, int month, int year);

    bool updateTaskTitle(int index, const std::string& title);
    bool updateTaskDescription(int index, const std::string& description);
    bool updateTaskStatus(int index, TaskStatus status);
    bool deleteTask(int index);

    bool isEmpty() const;
    int getTaskCount() const;

    /**
     * @brief Gets read-only access to the stored tasks vector.
     *
     * @return Constant reference to the internal vector of smart pointers to Task.
     */
    const std::vector<std::unique_ptr<Task>>& getTasks() const;
};

#endif