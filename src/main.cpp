#include "InputValidator.hpp"
#include "Menu.hpp"
#include "TaskList.hpp"

int main(void) {
    TaskList taskList;
    Menu menu;
    bool running = true;

    menu.addOption("Create a task", [&]() {
        menu.showMessage("-> Create a task");

        std::string title = InputValidator::readNonEmptyLine("Task title: ");
        TaskStatus status = menu.askStatus();

        taskList.addTask(title, status);
        menu.showMessage("\nTask created successfully.");
    });

    menu.addOption("Read task/s", [&]() {
        menu.showMessage("-> Read task/s");
        menu.displayTasks(taskList);
    });

    menu.addOption("Update task", [&]() {
        menu.showMessage("-> Update task");
        menu.displayTasks(taskList);

        if (taskList.getTaskCount() == 0) {
            return;
        }

        int position = menu.askTaskNumber(taskList);
        TaskStatus status = menu.askStatus();

        if (taskList.updateTaskStatus(position - 1, status)) {
            menu.showMessage("\nTask updated successfully.");
        } else {
            menu.showMessage("\nCould not update the task.");
        }
    });

    menu.addOption("Delete a task", [&]() {
        menu.showMessage("-> Delete a task");
        menu.displayTasks(taskList);

        if (taskList.getTaskCount() == 0) {
            return;
        }

        int position = menu.askTaskNumber(taskList);

        if (taskList.deleteTask(position - 1)) {
            menu.showMessage("\nTask deleted successfully.");
        } else {
            menu.showMessage("\nCould not delete the task.");
        }
    });

    menu.addOption("Exit", [&]() {
        menu.showMessage("Exiting...");
        running = false;
    });

    while (running) {
        int choice = menu.displayMenu();
        menu.execute(choice);

        if (running) {
            menu.pause();
        }
    }

    return 0;
}