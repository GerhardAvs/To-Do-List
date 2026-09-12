#include <iostream>
#include "Menu.hpp"
#include "TaskList.hpp"

/**
 * @brief Program entry point.
 *
 * @return 0 when the program terminates successfully.
 */
int main(void)
{
    TaskList taskList;
    Menu menu({ "Create a task", "Read task/s", "Update task", "Delete a task", "Exit" });

    int selectedOption = menu.displayMenu();

    switch (selectedOption)
    {
    case 1:
        menu.showMessage("-> Create a task");
        break;
    case 2:
        menu.displayTasks(taskList);
        break;
    case 3:
        menu.showMessage("-> Update task");
        break;
    case 4:
        menu.showMessage("-> Delete a task");
        break;
    case 5:
        menu.showMessage("Exiting...");
        break;
    }

    return 0;
}