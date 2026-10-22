#include "InputValidator.hpp"
#include "Menu.hpp"
#include "TaskList.hpp"

#include <exception>
#include <iostream>
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

        const TaskType type = menu.askTaskType();
        const std::string title = menu.askTitle();
        const std::string description = menu.askDescription();
        const TaskStatus status = menu.askStatus();
        bool created = true;

        // Each call below picks a different addTask() overload.
        if (type == TaskType::Normal) {
            taskList.addTask(title, description, status);
        } else if (type == TaskType::Priority) {
            const TaskPriority priority = menu.askPriority();
            taskList.addTask(title, description, status, priority);
        } else if (type == TaskType::WithDate) {
            int day = 1;
            int month = 1;
            int year = minYear;

            menu.askDate(day, month, year);
            created = taskList.addTask(title, description, status, day, month, year);
        }

        if (created) {
            menu.showMessage("\n>> Task created successfully.");
        } else {
            menu.showMessage("\n>> Could not create the task.");
        }
    });
}

/**
 * @brief Registers the read action on the menu.
 *
 * @param menu     Menu the option is added to.
 * @param taskList List whose tasks are shown.
 */
void registerReadOption(Menu& menu, const TaskList& taskList) {
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

        bool updated = taskList.updateTaskStatus(index, status);

        // Extra fields depend on the derived type of the selected task.
        if (taskList.isPriorityTask(index)) {
            const TaskPriority priority = menu.askPriority();
            updated = taskList.updateTaskPriority(index, priority) && updated;
        } else if (taskList.isTaskWithDate(index)) {
            int day = 1;
            int month = 1;
            int year = minYear;

            menu.askDate(day, month, year);
            updated = taskList.updateTaskDate(index, day, month, year) && updated;
        }

        if (updated) {
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
 * @return 0 when the program terminates successfully, 1 on an unexpected error.
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

    try {
        while (running) {
            const int choice = menu.displayMenu();
            menu.execute(choice);

            if (running) {
                menu.pause();
            }
        }
    } catch (const InputClosedError&) {
        // The user closed the input (Ctrl+D / Ctrl+Z): leave without looping.
        std::cout << "\n>> Input closed. Exiting..." << std::endl;
    } catch (const std::exception& error) {
        std::cerr << "\n>> Unexpected error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}