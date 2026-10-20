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

/**
 * @brief Constructs a task and records its creation timestamp.
 *
 * @param title Short name of the task.
 * @param description Detailed text explaining the task.
 * @param status Initial progress state of the task.
 */
Task::Task(const std::string& title, const std::string& description, TaskStatus status)
    : title(title),
      description(description),
      status(status),
      creationDate(buildCurrentTimestamp()) {
}

/**
 * @brief Gets the task title.
 *
 * @return Task title.
 */
const std::string& Task::getTitle() const { return this->title; }

/**
 * @brief Gets the task description.
 *
 * @return Task description.
 */
const std::string& Task::getDescription() const { return this->description; }

/**
 * @brief Gets the task status.
 *
 * @return Current task status.
 */
TaskStatus Task::getStatus() const { return this->status; }

/**
 * @brief Gets the task creation timestamp.
 *
 * @return Creation timestamp.
 */
const std::string& Task::getCreationDate() const { return this->creationDate; }

/**
 * @brief Sets the task title.
 *
 * @param title New title.
 */
void Task::setTitle(const std::string& title) { this->title = title; }

/**
 * @brief Sets the task description.
 *
 * @param description New description.
 */
void Task::setDescription(const std::string& description) { this->description = description; }

/**
 * @brief Sets the task status.
 *
 * @param status New progress state.
 */
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
