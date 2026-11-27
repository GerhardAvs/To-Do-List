#include "FileManager.hpp"

#include "FileException.hpp"
#include "PriorityTask.hpp"
#include "TaskWithDate.hpp"

#include <ctime>
#include <fstream>

namespace {

/** @brief Size of the buffer used to format "YYYY-MM-DD HH:MM:SS". */
constexpr std::size_t timestampBufferSize = 20;

/** @brief Bytes that mark a UTF-8 file, so Excel reads accents correctly. */
const char* const utf8Bom = "\xEF\xBB\xBF";

/**
 * @brief Builds the current local date and time as text.
 *
 * @return Timestamp formatted as "YYYY-MM-DD HH:MM:SS".
 */
std::string currentTimestamp() {
    const std::time_t now = std::time(nullptr);
    const std::tm* local = std::localtime(&now);

    if (local == nullptr) {
        return "Unknown time";
    }

    char buffer[timestampBufferSize] = { 0 };
    std::strftime(buffer, timestampBufferSize, "%Y-%m-%d %H:%M:%S", local);

    return std::string(buffer);
}

/**
 * @brief Prepares a value to be written as one CSV field.
 *
 * Fields with commas, quotes or line breaks go between quotes and their
 * quotes are doubled, as the CSV format requires.
 *
 * @param value Raw text.
 * @return Text ready to be placed between commas.
 */
std::string csvField(const std::string& value) {
    if (value.find_first_of(",\"\n\r") == std::string::npos) {
        return value;
    }

    std::string escaped = "\"";
    for (const char character : value) {
        if (character == '"') {
            escaped += "\"\"";
        } else {
            escaped += character;
        }
    }
    escaped += '"';

    return escaped;
}

}  // namespace

/**
 * @brief Creates the manager with the path of the log file.
 *
 * @param logPath Path of the log.
 */
FileManager::FileManager(const std::string& logPath)
    : logPath(logPath) {
}

/**
 * @brief Saves every task in a .csv file that Excel can open.
 *
 * Priority and due date are filled only for the types that have them.
 *
 * @param tasks Tasks to export.
 * @param filePath Path of the .csv file to create or overwrite.
 * @throws FileException If the file cannot be opened or written.
 */
void FileManager::exportToCsv(const std::vector<std::unique_ptr<Task>>& tasks, const std::string& filePath) const {
    std::ofstream file(filePath, std::ios::out | std::ios::trunc | std::ios::binary);

    if (!file.is_open()) {
        throw FileException(filePath, "Could not open the CSV file");
    }

    file << utf8Bom << "Type,Title,Description,Status,Created,Priority,Due date\r\n";

    for (const auto& task : tasks) {
        std::string priority;
        std::string dueDate;

        if (const auto* priorityTask = dynamic_cast<const PriorityTask*>(task.get())) {
            priority = priorityToString(priorityTask->getPriority());
        }

        if (const auto* dateTask = dynamic_cast<const TaskWithDate*>(task.get())) {
            dueDate = dateTask->getDate();
        }

        file << csvField(task->getTypeName()) << ','
             << csvField(task->getTitle()) << ','
             << csvField(task->getDescription()) << ','
             << csvField(statusToString(task->getStatus())) << ','
             << csvField(task->getCreationDate()) << ','
             << csvField(priority) << ','
             << csvField(dueDate) << "\r\n";
    }

    file.flush();
    if (!file) {
        throw FileException(filePath, "Could not write the CSV file");
    }
}

/**
 * @brief Appends one line with date, time, action and task to the log file.
 *
 * @param action What happened to the task.
 * @param task Task the action was applied to.
 * @throws FileException If the log file cannot be opened or written.
 */
void FileManager::logAction(LogAction action, const Task& task) const {
    std::ofstream file(this->logPath, std::ios::out | std::ios::app);

    if (!file.is_open()) {
        throw FileException(this->logPath, "Could not open the log file");
    }

    file << currentTimestamp() << " | " << logActionToString(action) << " | "
         << task.getTitle() << " (" << task.getTypeName() << ")\n";

    if (!file) {
        throw FileException(this->logPath, "Could not write the log file");
    }
}

/**
 * @brief Gets the path of the log file.
 *
 * @return Log file path.
 */
const std::string& FileManager::getLogPath() const {
    return this->logPath;
}

/**
 * @brief Converts a LogAction into the word written in the log.
 *
 * @param action Action to convert.
 * @return "ADDED", "COMPLETED", "REOPENED" or "DELETED".
 */
std::string logActionToString(LogAction action) {
    switch (action) {
        case LogAction::Added:
            return "ADDED";
        case LogAction::Completed:
            return "COMPLETED";
        case LogAction::Reopened:
            return "REOPENED";
        case LogAction::Deleted:
            return "DELETED";
    }

    return "UNKNOWN";
}
