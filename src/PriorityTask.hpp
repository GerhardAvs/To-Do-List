#ifndef PRIORITY_TASK_HPP
#define PRIORITY_TASK_HPP

#include "Task.hpp"

/**
 * @brief Represents the urgency level of a task.
 */
enum class TaskPriority {
    Low = 1,
    Medium = 2,
    High = 3
};

/**
 * @brief Derived class representing a task with a priority level.
 */
class PriorityTask : public Task {
private:
    TaskPriority priority;

public:
    /**
     * @brief Constructs a PriorityTask object.
     * 
     * @param title Short name of the task.
     * @param description Detailed description of the task.
     * @param status Initial progress state.
     * @param priority Task priority level (Low, Medium, High).
     */
    PriorityTask(const std::string& title, const std::string& description, TaskStatus status, TaskPriority priority);

    TaskPriority getPriority() const;
    void setPriority(TaskPriority priority);

    /**
     * @brief Prints task details including the priority level.
     * 
     * @param os Output stream to write to.
     */
    void printDetails(std::ostream& os = std::cout) const override;
};

std::string priorityToString(TaskPriority priority);

#endif