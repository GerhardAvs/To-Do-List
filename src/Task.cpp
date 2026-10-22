#include "Task.hpp"

#include <ctime>

namespace {

/** @brief Size of the buffer used to format "YYYY-MM-DD HH:MM". */
constexpr std::size_t dateBufferSize = 20;

/**
 * @brief Builds the current local date and time as text.
 *
 * @return Timestamp formatted as "YYYY-MM-DD HH:MM", or "Unknown" on failure.
 */
std::string buildCurrentTimestamp() {
    const std::time_t currentTime = std::time(nullptr);
    const std::tm* localTime = std::localtime(&currentTime);

    if (localTime == nullptr) {
        return "Unknown";
    }

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
 * @brief Overload: constructs a Pending task.
 *
 * @param title Short name of the task.
 * @param description Detailed text explaining the task.
 */
Task::Task(const std::string& title, const std::string& description)
    : Task(title, description, TaskStatus::Pending) {
}

/**
 * @brief Gets the task title.
 *
 * @return Task title.
 */
const std::string& Task::getTitle() const {
    return this->title;
}

/**
 * @brief Gets the task description.
 *
 * @return Task description.
 */
const std::string& Task::getDescription() const {
    return this->description;
}

/**
 * @brief Gets the task status.
 *
 * @return Current task status.
 */
TaskStatus Task::getStatus() const {
    return this->status;
}

/**
 * @brief Gets the task creation timestamp.
 *
 * @return Creation timestamp.
 */
const std::string& Task::getCreationDate() const {
    return this->creationDate;
}

/**
 * @brief Sets the task title.
 *
 * @param title New title.
 */
void Task::setTitle(const std::string& title) {
    this->title = title;
}

/**
 * @brief Sets the task description.
 *
 * @param description New description.
 */
void Task::setDescription(const std::string& description) {
    this->description = description;
}

/**
 * @brief Sets the task status.
 *
 * @param status New progress state.
 */
void Task::setStatus(TaskStatus status) {
    this->status = status;
}

/**
 * @brief Names the kind of task.
 *
 * @return "Normal".
 */
std::string Task::getTypeName() const {
    return "Normal";
}

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

/**
 * @brief Operator overload: prints any task (base or derived) with <<.
 *
 * @param os Output stream to write to.
 * @param task Task to print.
 * @return The same stream, to allow chaining.
 */
std::ostream& operator<<(std::ostream& os, const Task& task) {
    task.printDetails(os);
    return os;
}

/**
 * @brief Converts a status into its display name.
 *
 * @param status Status to convert.
 * @return "Pending", "In progress", "Completed" or "Unknown".
 */
std::string statusToString(TaskStatus status) {
    switch (status) {
        case TaskStatus::Pending:
            return "Pending";
        case TaskStatus::InProgress:
            return "In progress";
        case TaskStatus::Completed:
            return "Completed";
    }

    return "Unknown";
}

/**
 * @brief Converts a menu number into a TaskStatus.
 *
 * @param value Number selected by the user (1-3).
 * @return Matching status, or Pending when the number is unknown.
 */
TaskStatus statusFromInt(int value) {
    switch (value) {
        case static_cast<int>(TaskStatus::InProgress):
            return TaskStatus::InProgress;
        case static_cast<int>(TaskStatus::Completed):
            return TaskStatus::Completed;
        default:
            return TaskStatus::Pending;
    }
}