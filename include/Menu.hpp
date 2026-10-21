#ifndef MENU_HPP
#define MENU_HPP

#include "TaskList.hpp"
#include "PriorityTask.hpp"

#include <functional>
#include <string>
#include <vector>

/**
 * @brief Represents the available task types for creation.
 */
enum class TaskType {
    Normal = 1,
    Priority = 2,
    WithDate = 3
};

/** @brief Amount of values declared in TaskType. */
constexpr int taskTypeCount = 3;

/**
 * @brief A menu entry: the text shown and the action it runs.
 */
struct MenuOption {
    std::string label;
    std::function<void()> action;
};

/**
 * @brief Console interface of the application. Owns every prompt and every print.
 */
class Menu {
private:
    std::vector<MenuOption> options;

    void render() const;

public:
    void addOption(const std::string& label, std::function<void()> action);

    int displayMenu() const;
    void execute(int choice) const;

    /**
     * @brief Prints every task stored in a list using polymorphic dynamic dispatch.
     *
     * @param taskList The list whose tasks are printed.
     */
    void displayTasks(const TaskList& taskList) const;
    void showMessage(const std::string& message) const;
    void pause() const;

    std::string askTitle() const;
    std::string askTitleOrKeep() const;
    std::string askDescription() const;
    std::string askDescriptionOrKeep() const;
    TaskStatus askStatus() const;
    TaskType askTaskType() const;
    int askTaskIndex(const TaskList& taskList) const;

    /**
     * @brief Prompts the user to select a priority level for a PriorityTask.
     *
     * @return The selected TaskPriority value.
     */
    TaskPriority askPriority() const;

    /**
     * @brief Prompts the user to input day, month, and year values for a TaskWithDate.
     *
     * @param day Reference parameter to store the day.
     * @param month Reference parameter to store the month.
     * @param year Reference parameter to store the year.
     */
    void askDate(int& day, int& month, int& year) const;
};

#endif