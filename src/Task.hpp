#ifndef TASK_HPP
#define TASK_HPP

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
 * @brief A single to-do entry: what to do, how it is going and when it was created.
 */
class Task {
private:
    std::string title;
    std::string description;
    TaskStatus status;
    std::string creationDate;

public:
    Task(const std::string& title, const std::string& description, TaskStatus status);

    const std::string& getTitle() const;
    const std::string& getDescription() const;
    TaskStatus getStatus() const;
    const std::string& getCreationDate() const;

    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setStatus(TaskStatus status);
};

std::string statusToString(TaskStatus status);
TaskStatus statusFromInt(int value);

#endif