#include "Task.hpp"

#include <ctime>

Task::Task(const std::string& description, TaskStatus status) {
    this->description = description;
    this->status = status;

    const std::time_t currentTime = std::time(nullptr);
    std::string date = std::ctime(&currentTime);
    date.pop_back();
    this->creationDate = date;
}

std::string Task::getDescription() const {
    return this->description;
}

TaskStatus Task::getStatus() const {
    return this->status;
}

std::string Task::getCreationDate() const {
    return this->creationDate;
}

void Task::setStatus(TaskStatus status) {
    this->status = status;
}

std::string statusToString(TaskStatus status) {
    if (status == TaskStatus::Pending) {
        return "Pending";
    }
    if (status == TaskStatus::InProgress) {
        return "In progress";
    }
    return "Completed";
}
