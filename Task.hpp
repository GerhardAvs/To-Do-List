#ifndef TASK_HPP
#define TASK_HPP

#include <string>

enum class TaskStatus {
    Pending = 1,
    InProgress = 2,
    Completed = 3
};

class Task {
private:
    std::string description;
    TaskStatus status;
    std::string creationDate;

public:
    Task(const std::string& description, TaskStatus status);

    std::string getDescription() const;
    TaskStatus getStatus() const;
    std::string getCreationDate() const;

    void setStatus(TaskStatus status);
};

std::string statusToString(TaskStatus status);

#endif
