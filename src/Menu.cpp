#include "Menu.hpp"
#include "InputValidator.hpp"
#include "TaskWithDate.hpp"

#include <cstdlib>
#include <iostream>

namespace {

/** @brief Decorative separator drawn by the menu. */
const std::string separatorLine = "────────────────────────────────────────────────";

}  // namespace

/**
 * @brief Adds a new option together with the action it must run.
 *
 * @param label Text shown in the menu.
 * @param action Function executed when the option is selected.
 */
void Menu::addOption(const std::string& label, std::function<void()> action) {
    this->options.push_back({ label, action });
}

/**
 * @brief Draws the header and the list of registered options.
 */
void Menu::render() const {
    std::cout << "╔══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         C++ To Do List Manager               ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;

    for (std::size_t i = 0; i < this->options.size(); ++i) {
        const bool isLastOption = (i + 1 == this->options.size());

        if (isLastOption) {
            std::cout << std::endl;
        }

        std::cout << "  [" << (i + 1) << "] " << this->options[i].label << std::endl;
    }

    std::cout << separatorLine << std::endl;
    std::cout << "Select an option: ";
}

/**
 * @brief Clears the screen, draws the menu and reads a valid option.
 *
 * @return The option number selected by the user.
 */
int Menu::displayMenu() const {
    system("clear");
    this->render();

    return InputValidator::readIntInRange(1, static_cast<int>(this->options.size()));
}

/**
 * @brief Runs the action bound to the selected option.
 *
 * @param choice The option number selected by the user.
 */
void Menu::execute(int choice) const {
    this->options.at(choice - 1).action();
}

/**
 * @brief Prints every task stored in a list, numbered from one.
 * Uses dynamic dispatch via printDetails() to print sub-class specifics.
 *
 * @param taskList The list whose tasks are printed.
 */
void Menu::displayTasks(const TaskList& taskList) const {
    if (taskList.isEmpty()) {
        std::cout << ">> No tasks available." << std::endl;
        return;
    }

    const auto& tasks = taskList.getTasks();

    std::cout << "\n--- TASK LIST (" << tasks.size() << ") ---" << std::endl;

    for (std::size_t i = 0; i < tasks.size(); ++i) {
        const Task& task = *tasks[i];

        std::cout << "  [" << (i + 1) << "] " << task.getTitle() << std::endl;
        
        // Polymorphic call to the virtual printDetails() function.
        task.printDetails(std::cout);
        std::cout << std::endl;
    }
}

/**
 * @brief Prints a message on its own line.
 *
 * @param message The text to print.
 */
void Menu::showMessage(const std::string& message) const {
    std::cout << message << std::endl;
}

/**
 * @brief Waits for the user to press Enter before the menu is drawn again.
 */
void Menu::pause() const {
    std::cout << "\n>> Press Enter to continue...";
    std::cin.get();
}

/**
 * @brief Asks for a task title and rejects empty text.
 *
 * @return The title entered by the user.
 */
std::string Menu::askTitle() const {
    return InputValidator::readNonEmptyLine("Task title: ");
}

/**
 * @brief Asks for a new title, letting the user keep the current one.
 *
 * @return The new title, or an empty string to keep the current one.
 */
std::string Menu::askTitleOrKeep() const {
    return InputValidator::readLine("New title (Enter to keep it): ");
}

/**
 * @brief Asks for a task description and rejects empty text.
 *
 * @return The description entered by the user.
 */
std::string Menu::askDescription() const {
    return InputValidator::readNonEmptyLine("Task description: ");
}

/**
 * @brief Asks for a new description, letting the user keep the current one.
 *
 * @return The new description, or an empty string to keep the current one.
 */
std::string Menu::askDescriptionOrKeep() const {
    return InputValidator::readLine("New description (Enter to keep it): ");
}

/**
 * @brief Shows the available progress states and reads the chosen one.
 *
 * @return The status selected by the user.
 */
TaskStatus Menu::askStatus() const {
    std::cout << std::endl;
    std::cout << "  [" << static_cast<int>(TaskStatus::Pending)    << "] Pending"     << std::endl;
    std::cout << "  [" << static_cast<int>(TaskStatus::InProgress) << "] In progress" << std::endl;
    std::cout << "  [" << static_cast<int>(TaskStatus::Completed)  << "] Completed"   << std::endl;
    std::cout << "Select a progress state: ";

    return statusFromInt(InputValidator::readIntInRange(1, taskStatusCount));
}

/**
 * @brief Asks the user to pick a task by its listed number.
 *
 * @param taskList The list the user is choosing from.
 * @return The zero-based index of the chosen task.
 */
int Menu::askTaskIndex(const TaskList& taskList) const {
    std::cout << "\nTask number: ";

    return InputValidator::readIntInRange(1, taskList.getTaskCount()) - 1;
}

/**
 * @brief Prompts the user to select a priority level for a PriorityTask.
 *
 * @return The selected TaskPriority value.
 */
TaskPriority Menu::askPriority() const {
    std::cout << std::endl;
    std::cout << "  [" << static_cast<int>(TaskPriority::Low)    << "] Low"    << std::endl;
    std::cout << "  [" << static_cast<int>(TaskPriority::Medium) << "] Medium" << std::endl;
    std::cout << "  [" << static_cast<int>(TaskPriority::High)   << "] High"   << std::endl;
    std::cout << "Select priority level: ";

    int choice = InputValidator::readIntInRange(1, taskPriorityCount);
    return static_cast<TaskPriority>(choice);
}

/**
 * @brief Prompts the user to input day, month, and year values for a TaskWithDate.
 *
 * @param day Reference parameter to store the day.
 * @param month Reference parameter to store the month.
 * @param year Reference parameter to store the year.
 */
void Menu::askDate(int& day, int& month, int& year) const {
    std::cout << "\nEnter target date details:" << std::endl;
    std::cout << "  Year (" << minYear << "-" << maxYear << "): ";
    year = InputValidator::readIntInRange(minYear, maxYear);

    std::cout << "  Month (1-12): ";
    month = InputValidator::readIntInRange(1, 12);

    const int lastDay = daysInMonth(month, year);

    std::cout << "  Day (1-" << lastDay << "): ";
    day = InputValidator::readIntInRange(1, lastDay);
}
