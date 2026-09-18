#include <iostream>

#include "Menu.hpp"
#include "TaskList.hpp"

int main(void) {
    TaskList taskList;
    Menu menu;
    bool running = true;

    menu.addOption("Create a task", [&]() { 
        menu.showMessage("-> Create a task");
        TaskList::addTask("hola", TaskStatus = 1);
    });

    menu.addOption("Read task/s",   [&]() { 
        menu.displayTasks(taskList); 
        std::cout << "you have: " << TaskList::getTaskCount() << std::endl;
        std::cout << TaskList::getTasks();
    });

    menu.addOption("Update task",   [&]() { 
        menu.showMessage("-> Update task");

     });

    menu.addOption("Delete a task", [&]() { 
        menu.showMessage("-> Delete a task"); 
    });

    
    menu.addOption("Exit",          [&]() {
        menu.showMessage("Exiting...");
        running = false;
    });

    while (running) {
        int choice = menu.displayMenu();
        menu.execute(choice);
    }

    return 0;
}