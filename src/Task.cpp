#include "Task.hpp"
#include <ctime>

namespace {

constexpr std::size_t dateBufferSize = 20;

std::string buildCurrentTimestamp() {
    const std::time_t currentTime = std::time(nullptr);
    const std::tm* localTime = std::localtime(&currentTime);

    char buffer[dateBufferSize] = { 0 };
    std::strftime(buffer, dateBufferSize, "%Y-%m-%d %H:%M", localTime);

    return std::string(buffer);
}

}  // namespace

Task::Task(const std::string& title, const std::string& description, TaskStatus status)
    : title(title),
      description(description),
      status(status),
      creationDate(buildCurrentTimestamp()) {
}

const std::string& Task::getTitle() const { return this->title; }
const std::string& Task::getDescription() const { return this->description; }
TaskStatus Task::getStatus() const { return this->status; }
const std::string& Task::getCreationDate() const { return this->creationDate; }

void Task::setTitle(const std::string& title) { this->title = title; }
void Task::setDescription(const std::string& description) { this->description = description; }
void Task::setStatus(TaskStatus status) { this->status = status; }

/**
 * @brief Prints the base details of the task to the given stream.
 * 
 * @param os Output stream to print to.
     */
void Task::printDetails(std::ostream& os) const {
    os << "      Description: " << this->description << "\n";
    os << "      Status: " << statusToString(this->status)
       << " | Created: " << this->creationDate;
}

std::string statusToString(TaskStatus status) {
    if (status == TaskStatus::Pending) return "Pending";
    if (status == TaskStatus::InProgress) return "In progress";
    return "Completed";
}

TaskStatus statusFromInt(int value) {
    if (value == static_cast<int>(TaskStatus::InProgress)) return TaskStatus::InProgress;
    if (value == static_cast<int>(TaskStatus::Completed)) return TaskStatus::Completed;
    return TaskStatus::Pending;
}