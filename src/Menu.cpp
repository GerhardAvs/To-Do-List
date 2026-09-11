#include <iostream>
#include <cstdlib>
#include <limits>

#include "Menu.hpp"
#include "InputValidator.hpp"

Menu::Menu(std::vector<std::string> ops) : option(ops) {}

/**
 * @brief Displays the main menu and reads a valid user option.
 *
 * @return The selected menu option, from 1 to 5.
 */
void Menu::render(void) const{
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

int Menu::displayMenu() const{
    system("clear");
    Menu::render();

    return InputValidator::readIntInRange(1, static_cast<int>(option.size()));
}
