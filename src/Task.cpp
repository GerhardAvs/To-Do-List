#include "Task.hpp"

#include <ctime>

namespace {

/** @brief Length of the "YYYY-MM-DD HH:MM" buffer, including the null byte. */
constexpr std::size_t dateBufferSize = 20;

/**
 * @brief Builds a readable timestamp for the current local time.
 *
 * @return The current date and time as "YYYY-MM-DD HH:MM".
 */
std::string buildCurrentTimestamp() {
    const std::time_t currentTime = std::time(nullptr);
    const std::tm* localTime = std::localtime(&currentTime);

    char buffer[dateBufferSize] = { 0 };
    std::strftime(buffer, dateBufferSize, "%Y-%m-%d %H:%M", localTime);

    return std::string(buffer);
}

}  // namespace

/**
 * @brief Builds a task and stamps it with the current date and time.
 *
 * @param title       Short name of the task.
 * @param description Detailed text explaining the task.
 * @param status      Initial progress state of the task.
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
 * @return Constant reference to the title.
 */
const std::string& Task::getTitle() const {
    return this->title;
}

/**
 * @brief Gets the task description.
 *
 * @return Constant reference to the description.
 */
const std::string& Task::getDescription() const {
    return this->description;
}

/**
 * @brief Gets the current progress state of the task.
 *
 * @return The status of the task.
 */
TaskStatus Task::getStatus() const {
    return this->status;
}

/**
 * @brief Gets the moment the task was created.
 *
 * @return Constant reference to the creation date.
 */
const std::string& Task::getCreationDate() const {
    return this->creationDate;
}

/**
 * @brief Replaces the task title.
 *
 * @param title The new title.
 */
void Task::setTitle(const std::string& title) {
    this->title = title;
}

/**
 * @brief Replaces the task description.
 *
 * @param description The new description.
 */
void Task::setDescription(const std::string& description) {
    this->description = description;
}

/**
 * @brief Replaces the task progress state.
 *
 * @param status The new status.
 */
void Task::setStatus(TaskStatus status) {
    this->status = status;
}

/**
 * @brief Converts a status into readable text.
 *
 * @param status The status to convert.
 * @return The display name of the status.
 */
std::string statusToString(TaskStatus status) {
    if (status == TaskStatus::Pending) {
        return "Pending";
    }

    if (status == TaskStatus::InProgress) {
        return "In progress";
    }

    return "Completed";
}

/**
 * @brief Converts a menu number into its matching status.
 *
 * @param value Number from 1 to taskStatusCount entered by the user.
 * @return The matching status, or TaskStatus::Pending when the value is unknown.
 */
TaskStatus statusFromInt(int value) {
    if (value == static_cast<int>(TaskStatus::InProgress)) {
        return TaskStatus::InProgress;
    }

    if (value == static_cast<int>(TaskStatus::Completed)) {
        return TaskStatus::Completed;
    }

    return TaskStatus::Pending;
}