#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <string>

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
     * @brief Overload: constructs a Pending task.
     *
     * @param title Short name of the task.
     * @param description Detailed text explaining the task.
     */
    Task(const std::string& title, const std::string& description);

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
     * @brief Polymorphic function that names the kind of task.
     *
     * @return "Normal" for the base class; derived classes override it.
     */
    virtual std::string getTypeName() const;

    /**
     * @brief Polymorphic function to print detailed information of the task.
     *
     * @param os Output stream where the details will be printed. Defaults to std::cout.
     */
    virtual void printDetails(std::ostream& os = std::cout) const;
};

/**
 * @brief Operator overload: prints any task (base or derived) with <<.
 *
 * Calls the virtual printDetails(), so the derived version is used.
 *
 * @param os Output stream to write to.
 * @param task Task to print.
 * @return The same stream, to allow chaining.
 */
std::ostream& operator<<(std::ostream& os, const Task& task);

std::string statusToString(TaskStatus status);
TaskStatus statusFromInt(int value);

#endif  // TASK_HPP