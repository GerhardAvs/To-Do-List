#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include "TaskList.hpp"

/**
 * @brief Manages the user interface and menu display.
 */
class Menu {
private:
    std::vector<std::string> option;

public:
    /**
     * @brief Constructs a new Menu object.
     *
     * @param option List of options to display in the menu.
     */
    Menu(std::vector<std::string> option);

    /**
     * @brief Renders the menu elements on the screen.
     */
    void render() const;

    /**
     * @brief Clears the screen, renders the menu, and reads the user's choice.
     *
     * @return The selected menu option index.
     */
    int displayMenu() const;

    /**
     * @brief Displays the list of tasks on the screen.
     *
     * @param taskList Reference to the TaskList containing tasks to print.
     */
    void displayTasks(const TaskList& taskList) const;

    /**
     * @brief Displays a message to the user.
     *
     * @param message Text message to be displayed.
     */
    void showMessage(const std::string& message) const;
};

#endif
