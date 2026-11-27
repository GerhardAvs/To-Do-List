#include "FileException.hpp"
#include "FileManager.hpp"
#include "TaskList.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

namespace {

int failures = 0;

/**
 * @brief Prints OK or FAIL for one check.
 *
 * @param condition Result of the check.
 * @param name What was checked.
 */
void check(bool condition, const std::string& name) {
    std::cout << (condition ? "  OK    " : "  FAIL  ") << name << '\n';
    if (!condition) {
        ++failures;
    }
}

/**
 * @brief Reads a whole file as text.
 *
 * @param path File to read.
 * @return Its content, or an empty string when it cannot be opened.
 */
std::string readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    std::stringstream content;
    content << file.rdbuf();
    return content.str();
}

}  // namespace

/**
 * @brief Tests exportToCsv(), logAction() and the FileException errors.
 *
 * @return 0 when every check passes, 1 otherwise.
 */
int main() {
    const std::string csvPath = "test_tasks.csv";
    const std::string logPath = "test_log.txt";
    std::remove(csvPath.c_str());
    std::remove(logPath.c_str());

    TaskList list;
    list.addTask("Comprar pan", "En la tienda, la de la esquina", TaskStatus::Pending);
    list.addTask("Entregar fase 3", "Subir el \"proyecto\"", TaskStatus::InProgress, TaskPriority::High);
    list.addTask("Examen de POO", "Repasar herencia", TaskStatus::Completed, 26, 11, 2026);

    FileManager files(logPath);

    std::cout << "exportToCsv()\n";
    files.exportToCsv(list.getTasks(), csvPath);
    const std::string csv = readFile(csvPath);
    check(csv.rfind("\xEF\xBB\xBF" "Type,Title,Description,Status,Created,Priority,Due date\r\n", 0) == 0,
          "starts with the UTF-8 BOM and the header row");
    check(csv.find("Normal,Comprar pan,\"En la tienda, la de la esquina\",Pending,") != std::string::npos,
          "a description with a comma goes between quotes");
    check(csv.find("Entregar fase 3,\"Subir el \"\"proyecto\"\"\",In progress,") != std::string::npos,
          "quotes inside a field are doubled");
    check(csv.find(",High,\r\n") != std::string::npos, "priority column filled only for the priority task");
    check(csv.find(",Completed,") != std::string::npos && csv.find(",2026-11-26\r\n") != std::string::npos,
          "status and due date of the dated task");

    std::cout << "logAction()\n";
    files.logAction(LogAction::Added, *list.getTask(0));
    files.logAction(LogAction::Completed, *list.getTask(0));
    files.logAction(LogAction::Deleted, *list.getTask(1));
    const std::string log = readFile(logPath);
    check(log.find(" | ADDED | Comprar pan (Normal)\n") != std::string::npos, "ADDED line written");
    check(log.find(" | COMPLETED | Comprar pan (Normal)\n") != std::string::npos, "COMPLETED line written");
    check(log.find(" | DELETED | Entregar fase 3 (Priority)\n") != std::string::npos, "DELETED line written");
    check(log.size() > 20 && log[4] == '-' && log[13] == ':', "each line starts with date and time");
    std::cout << "\n--- log.txt ---\n" << log << "---------------\n\n";

    std::cout << "FileException\n";
    bool thrown = false;
    try {
        files.exportToCsv(list.getTasks(), "folder_that_does_not_exist/tasks.csv");
    } catch (const FileException& error) {
        thrown = true;
        std::cout << "  what(): " << error.what() << '\n';
    }
    check(thrown, "exportToCsv throws FileException when the file cannot be opened");

    thrown = false;
    try {
        FileManager("folder_that_does_not_exist/log.txt").logAction(LogAction::Added, *list.getTask(0));
    } catch (const FileException&) {
        thrown = true;
    }
    check(thrown, "logAction throws FileException when the log cannot be opened");

    std::remove(csvPath.c_str());
    std::remove(logPath.c_str());
    std::cout << (failures == 0 ? "\nAll checks passed\n" : "\nSome checks failed\n");
    return failures == 0 ? 0 : 1;
}
