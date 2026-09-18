#include "Menu.hpp"
#include "TaskList.hpp"

#include <string>

/**
 * @brief Registers the create action on the menu.
 *
 * @param menu     Menu the option is added to.
 * @param taskList List the new task is stored in.
 */
void registerCreateOption(Menu& menu, TaskList& taskList) {
    menu.addOption("Create a task", [&menu, &taskList]() {
        menu.showMessage("-> Create a task");

        const std::string title = menu.askTitle();
        const std::string description = menu.askDescription();
        const TaskStatus status = menu.askStatus();

        taskList.addTask(title, description, status);
        menu.showMessage("\n>> Task created successfully.");
    });
}

/**
 * @brief Registers the read action on the menu.
 *
 * @param menu     Menu the option is added to.
 * @param taskList List whose tasks are shown.
 */
void registerReadOption(Menu& menu, TaskList& taskList) {
    menu.addOption("Read task/s", [&menu, &taskList]() {
        menu.showMessage("-> Read task/s");
        menu.displayTasks(taskList);
    });
}

/**
 * @brief Registers the update action on the menu.
 *
 * @param menu     Menu the option is added to.
 * @param taskList List holding the task to update.
 */
void registerUpdateOption(Menu& menu, TaskList& taskList) {
    menu.addOption("Update task", [&menu, &taskList]() {
        menu.showMessage("-> Update task");
        menu.displayTasks(taskList);

        if (taskList.isEmpty()) {
            return;
        }

        const int index = menu.askTaskIndex(taskList);
        const std::string title = menu.askTitleOrKeep();
        const std::string description = menu.askDescriptionOrKeep();
        const TaskStatus status = menu.askStatus();

        if (!title.empty()) {
            taskList.updateTaskTitle(index, title);
        }

        if (!description.empty()) {
            taskList.updateTaskDescription(index, description);
        }

        if (taskList.updateTaskStatus(index, status)) {
            menu.showMessage("\n>> Task updated successfully.");
        } else {
            menu.showMessage("\n>> Could not update the task.");
        }
    });
}

/**
 * @brief Registers the delete action on the menu.
 *
 * @param menu     Menu the option is added to.
 * @param taskList List the task is removed from.
 */
void registerDeleteOption(Menu& menu, TaskList& taskList) {
    menu.addOption("Delete a task", [&menu, &taskList]() {
        menu.showMessage("-> Delete a task");
        menu.displayTasks(taskList);

        if (taskList.isEmpty()) {
            return;
        }

        const int index = menu.askTaskIndex(taskList);

        if (taskList.deleteTask(index)) {
            menu.showMessage("\n>> Task deleted successfully.");
        } else {
            menu.showMessage("\n>> Could not delete the task.");
        }
    });
}

/**
 * @brief Registers the exit action on the menu.
 *
 * @param menu    Menu the option is added to.
 * @param running Flag turned off to leave the main loop.
 */
void registerExitOption(Menu& menu, bool& running) {
    menu.addOption("Exit", [&menu, &running]() {
        menu.showMessage("Exiting...");
        running = false;
    });
}

/**
 * @brief Program entry point. Builds the menu and runs it until the user exits.
 *
 * @return 0 when the program terminates successfully.
 */
int main() {
    TaskList taskList;
    Menu menu;
    bool running = true;

    registerCreateOption(menu, taskList);
    registerReadOption(menu, taskList);
    registerUpdateOption(menu, taskList);
    registerDeleteOption(menu, taskList);
    registerExitOption(menu, running);

    while (running) {
        const int choice = menu.displayMenu();
        menu.execute(choice);

        if (running) {
            menu.pause();
        }
    }

    return 0;
}