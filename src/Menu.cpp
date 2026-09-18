#include <iostream>

#include "Menu.hpp"
#include "InputValidator.hpp"

/**
 * @brief Adds a new option with the action it must run.
 *
 * @param label  Text shown in the menu.
 * @param action Function executed when the option is selected.
 */
void Menu::addOption(const std::string& label, std::function<void()> action) {
    options.push_back({ label, action });
}

/**
 * @brief Renders the header and option list of the main menu.
 */
void Menu::render(void) const {
    std::cout << "╔══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         C++ To Do List Manager               ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;

    for (size_t i = 0; i < options.size(); ++i) {
        if (i + 1 == options.size()) {
            std::cout << std::endl;
        }

        std::cout << "  [" << (i + 1) << "] " << options[i].label << std::endl;
    }

    std::cout << "────────────────────────────────────────────────" << std::endl;
    std::cout << "Select an option: ";
}

/**
 * @brief Displays the main menu and reads a valid user option.
 *
 * @return The selected menu option.
 */
int Menu::displayMenu() const {
    system("clear");
    render();

    return InputValidator::readIntInRange(1, static_cast<int>(options.size()));
}

/**
 * @brief Runs the action bound to the selected option.
 *
 * @param choice The option number selected by the user.
 */
void Menu::execute(int choice) const {
    options.at(choice - 1).action();
}
/**
 * @brief Prints all tasks contained in a TaskList.
 *
 * @param taskList Reference to the TaskList to be printed.
 */
void Menu::displayTasks(const TaskList& taskList) const {
    const std::vector<Task>& tasks = taskList.getTasks();

    if (tasks.empty()) {
        std::cout << ">> No tasks available." << std::endl;
        return;
    }

    std::cout << "\n--- TASK LIST (" << tasks.size() << ") ---" << std::endl;

    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << "  [" << (i + 1) << "] "
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

/**
 * @brief Waits for the user to press Enter before redrawing the menu.
 */
void Menu::pause() const {
    std::cout << "\n>> Press Enter to continue...";
    std::cin.get();
}

/**
 * @brief Asks the user for a task status.
 *
 * @return The TaskStatus chosen by the user.
 */
TaskStatus Menu::askStatus() const {
    std::cout << "\n─────────────────────────────" << std::endl;
    std::cout << "  [1] Pending" << std::endl;
    std::cout << "  [2] In progress" << std::endl;
    std::cout << "  [3] Completed" << std::endl;
    std::cout << "─────────────────────────────" << std::endl;
    std::cout << "Select a number of status: ";

    return statusFromInt(InputValidator::readIntInRange(1, 3));
}

/**
 * @brief Asks the user to pick an existing task by its listed number.
 *
 * @param taskList Reference to the TaskList being shown.
 * @return The task number, from 1 to the amount of tasks.
 */
int Menu::askTaskNumber(const TaskList& taskList) const {
    std::cout << "\nTask number: ";

    return InputValidator::readIntInRange(1, taskList.getTaskCount());
}