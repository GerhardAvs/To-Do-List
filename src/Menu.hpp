#ifndef MENU_HPP
#define MENU_HPP

#include "TaskList.hpp"

#include <functional>
#include <string>
#include <vector>

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

    void displayTasks(const TaskList& taskList) const;
    void showMessage(const std::string& message) const;
    void pause() const;

    std::string askTitle() const;
    std::string askTitleOrKeep() const;
    std::string askDescription() const;
    std::string askDescriptionOrKeep() const;
    TaskStatus askStatus() const;
    int askTaskIndex(const TaskList& taskList) const;
};

#endif