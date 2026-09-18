#pragma once

#include <functional>
#include <string>
#include <vector>

#include "TaskList.hpp"

/**
 * @brief A menu entry: the text shown and the action it runs.
 */
struct MenuOption {
    std::string label;
    std::function<void()> action;
};

class Menu {
public:
    void addOption(const std::string& label, std::function<void()> action);

    int  displayMenu() const;
    void execute(int choice) const;

    void displayTasks(const TaskList& taskList) const;
    void showMessage(const std::string& message) const;

private:
    void render(void) const;

    std::vector<MenuOption> options;
};