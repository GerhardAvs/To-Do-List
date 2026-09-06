#include <iostream>
#include <cstdlib>
#include <limits>

#include "menu.hpp"

/**
 * @brief Displays the main menu and reads a valid user option.
 *
 * @return The selected menu option, from 1 to 5.
 */
int displayMenu(void)
{
    int selectedOption = 0;

    do
    {
        system("clear");

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
        selectedOption = readOption();

    } while (selectedOption < 1 || selectedOption > 5);

    return selectedOption;
}

/**
 * @brief Executes the action associated with the selected menu option.
 *
 * @param selectedOption The menu option selected by the user.
 */
void menuSelection(int selectedOption)
{
    switch (selectedOption)
    {
        case 1:
            std::cout << "Selected option 1" << std::endl;
            break;

        case 2:
            std::cout << "Selected option 2" << std::endl;
            break;

        case 3:
            std::cout << "Selected option 3" << std::endl;
            break;

        case 4:
            std::cout << "Selected option 4" << std::endl;
            break;

        case 5:
            std::cout << "Selected option 5" << std::endl;
            break;
    }
}

/**
 * @brief Reads and validates a menu option from standard input.
 *
 * @return The selected option if valid, otherwise -1.
 */
int readOption(void)
{
    int selectedOption;

    std::cin >> selectedOption;

    if (std::cin.fail() || selectedOption < 1 || selectedOption > 5)
    {
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::cout << "\n>> Please Enter a valid option." << std::endl;
        std::cout << "Press Enter to restart...";
        std::cin.get();

        return -1;
    }

    return selectedOption;
}

