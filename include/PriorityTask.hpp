#ifndef PRIORITY_TASK_HPP
#define PRIORITY_TASK_HPP

#include "Task.hpp"

#include <string>

/**
 * @brief Represents the urgency level of a task.
 */
enum class TaskPriority {
    Low = 1,
    Medium = 2,
    High = 3
};

/** @brief Amount of values declared in TaskPriority. */
constexpr int taskPriorityCount = 3;

/**
 * @brief Derived class representing a task with a priority level.
 */
class PriorityTask : public Task {
private:
    TaskPriority priority;

    /**
     * @brief Converts text such as "high" or "alta" into a TaskPriority.
     *
     * @param level Text typed by the user.
     * @return Matching TaskPriority.
     * @throws std::invalid_argument If the text is not a known priority.
     */
    static TaskPriority stringToPriority(const std::string& level);

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

    /**
     * @brief Overload: constructs a Pending task with the given priority.
     *
     * @param title Short name of the task.
     * @param description Detailed description of the task.
     * @param priority Task priority level (Low, Medium, High).
     */
    PriorityTask(const std::string& title, const std::string& description, TaskPriority priority);

    /**
     * @brief Overload: constructs a Pending task with Medium priority.
     *
     * @param title Short name of the task.
     * @param description Detailed description of the task.
     */
    PriorityTask(const std::string& title, const std::string& description);

    TaskPriority getPriority() const;
    void setPriority(TaskPriority priority);

    /**
     * @brief Overload: sets the priority from text typed by the user.
     *
     * @param level "low", "medium" or "high" (also "baja", "media", "alta").
     * @throws std::invalid_argument If the text is not a known priority.
     */
    void setPriority(const std::string& level);

    /**
     * @brief Names the kind of task.
     *
     * @return "Priority".
     */
    std::string getTypeName() const override;

    /**
     * @brief Prints task details including the priority level.
     *
     * @param os Output stream to write to.
     */
    void printDetails(std::ostream& os = std::cout) const override;
};

std::string priorityToString(TaskPriority priority);
TaskPriority priorityFromInt(int value);

#endif  // PRIORITY_TASK_HPP