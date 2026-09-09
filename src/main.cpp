#include <iostream>
#include "Menu.hpp"

/**
 * @brief Program entry point.
 *
 * @return 0 when the program terminates successfully.
 */
int main(void)
{
    Menu menu({"Create a task", "Read task/s", "Update task", "Delete a task", "Exit"});
 
    int selectedOption = menu.displayMenu();
 
    switch (selectedOption)
    {
        case 1:
            std::cout << "-> Create a task" << std::endl;
            break;
        case 2:
            std::cout << "-> Read task/s" << std::endl;
            break;
        case 3:
            std::cout << "-> Update task" << std::endl;
            break;
        case 4:
            std::cout << "-> Delete a task" << std::endl;
            break;
        case 5:
            std::cout << "Exiting..." << std::endl;
            break;
    }
 
    return 0;
}
