#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <iostream>

/**
 * @brief Progress state a task can be in.
 */
enum class TaskStatus {
    Pending = 1,
    InProgress = 2,
    Completed = 3
};

/** @brief Amount of values declared in TaskStatus. */
constexpr int taskStatusCount = 3;

/**
 * @brief Base class representing a single to-do entry.
 */
class Task {
private:
    std::string title;
    std::string description;
    TaskStatus status;
    std::string creationDate;

public:
    /**
     * @brief Constructs a base Task with title, description, and status.
     * 
     * @param title Short name of the task.
     * @param description Detailed text explaining the task.
     * @param status Initial progress state of the task.
     */
    Task(const std::string& title, const std::string& description, TaskStatus status);

    /**
     * @brief Virtual destructor for polymorphic cleanup.
     */
    virtual ~Task() = default;

    const std::string& getTitle() const;
    const std::string& getDescription() const;
    TaskStatus getStatus() const;
    const std::string& getCreationDate() const;

    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setStatus(TaskStatus status);

    /**
     * @brief Polymorphic function to print detailed information of the task.
     * 
     * @param os Output stream where the details will be printed. Defaults to std::cout.
     */
    virtual void printDetails(std::ostream& os = std::cout) const;
};

std::string statusToString(TaskStatus status);
TaskStatus statusFromInt(int value);

#endif