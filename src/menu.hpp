#ifndef MENU_HPP
#define MENU_HPP

/**
 * @brief Displays the main menu and reads a valid user option.
 *
 * @return The selected menu option, from 1 to 5.
 */
int displayMenu(void);

/**
 * @brief Executes the action associated with the selected menu option.
 *
 * @param selectedOption The menu option selected by the user.
 */
void menuSelection(int selectedOption);

/**
 * @brief Reads and validates a menu option from standard input.
 *
 * @return The selected option if valid, otherwise -1.
 */
int readOption(void);

#endif

