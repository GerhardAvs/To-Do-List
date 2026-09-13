#include <iostream>
#include <cstdlib>
#include <limits>

#include "Menu.hpp"
#include "InputValidator.hpp"

Menu::Menu(std::vector<std::string> ops) : option(ops) {}

/**
 * @brief Renders the header and option list of the main menu.
 */
void Menu::render(void) const {
    std::cout << "╔══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         C++ To Do List Manager               ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════╝" << std::endl;
    std::cout << "                                                " << std::endl;
    std::cout << "  [1] Create a task                             " << std::endl;
    std::cout << "  [2] Read task/s                               " << std::endl;
    std::cout << "  [3] Update task                               " << std::endl;
    std::cout << "  [4] Delete a task                             " << std::endl;
    std::cout << std::endl;
    std::cout << "  [5] Exit                                      " << std::endl;
    std::cout << "────────────────────────────────────────────────" << std::endl;
    std::cout << "Select an option: ";
}

/**
 * @brief Displays the main menu and reads a valid user option.
 *
 * @return The selected menu option, from 1 to 5.
 */
int Menu::displayMenu() const {
    system("clear");
    Menu::render();

    return InputValidator::readIntInRange(1, static_cast<int>(option.size()));
}

/**
 * @brief Prints all tasks contained in a TaskList.
 *
 * @param taskList Reference to the TaskList to be printed.
 */
void Menu::displayTasks(const TaskList& taskList) const {
    const auto& tasks = taskList.getTasks();

    if (tasks.empty()) {
        std::cout << "No tasks available." << std::endl;
        return;
    }

    std::cout << "\n--- TASK LIST ---" << std::endl;
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << "[" << (i + 1) << "] "
            << tasks[i].getDescription()
            << " | Status: " << statusToString(tasks[i].getStatus())
            << " | Date: " << tasks[i].getCreationDate()
            << std::endl;
    }
}

/**
 * @brief Prints a message string to standard output.
 *
 * @param message The message string to print.
 */
void Menu::showMessage(const std::string& message) const {
    std::cout << message << std::endl;
}