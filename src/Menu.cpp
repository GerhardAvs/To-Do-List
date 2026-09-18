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