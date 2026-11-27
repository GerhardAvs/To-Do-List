#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include "Task.hpp"

#include <memory>
#include <string>
#include <vector>

/**
 * @brief Actions written in the log file.
 */
enum class LogAction {
    Added,
    Completed,
    Reopened,
    Deleted
};

/**
 * @brief File functions of the app: CSV export and the action log.
 *
 * Uses std::ofstream, so it has no Qt dependency and lives in the model library.
 * Every function throws FileException when its file cannot be opened.
 */
class FileManager {
private:
    std::string logPath;

public:
    /**
     * @brief Creates the manager with the path of the log file.
     *
     * @param logPath Path of the log; "log.txt" in the working folder by default.
     */
    explicit FileManager(const std::string& logPath = "log.txt");

    /**
     * @brief Saves every task in a .csv file that Excel can open.
     *
     * Columns: Type, Title, Description, Status, Created, Priority, Due date.
     * The file starts with a UTF-8 BOM so Excel shows accents correctly, and
     * fields with commas, quotes or line breaks are quoted.
     *
     * @param tasks Tasks to export (for example TaskList::getTasks()).
     * @param filePath Path of the .csv file to create or overwrite.
     * @throws FileException If the file cannot be opened or written.
     */
    void exportToCsv(const std::vector<std::unique_ptr<Task>>& tasks, const std::string& filePath) const;

    /**
     * @brief Appends one line with date, time, action and task to the log file.
     *
     * Example: "2026-11-25 20:31:07 | ADDED | Comprar pan (Normal)".
     *
     * @param action What happened to the task.
     * @param task Task the action was applied to.
     * @throws FileException If the log file cannot be opened or written.
     */
    void logAction(LogAction action, const Task& task) const;

    /**
     * @brief Gets the path of the log file.
     *
     * @return Log file path.
     */
    const std::string& getLogPath() const;
};

/**
 * @brief Converts a LogAction into the word written in the log.
 *
 * @param action Action to convert.
 * @return "ADDED", "COMPLETED", "REOPENED" or "DELETED".
 */
std::string logActionToString(LogAction action);

#endif  // FILE_MANAGER_HPP
