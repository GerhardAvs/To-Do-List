#include <iostream>
#include <limits>

#include "InputValidator.hpp"

/**
 * @brief Clears the standard input stream buffer.
 */
void InputValidator::clearInputBuffer(void) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Reads an integer input within a specified range.
 *
 * @param minValue Minimum allowed integer value.
 * @param maxValue Maximum allowed integer value.
 * @return Validated integer value entered by the user.
 */
int InputValidator::readIntInRange(int minValue, int maxValue) {
    int value = 0;
    bool isValid = false;

    do
    {
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            clearInputBuffer();
        }
        else if (value < minValue || value > maxValue)
        {
            std::cout << "Option out of range. Please try again." << std::endl;
            clearInputBuffer();
        }
        else
        {
            isValid = true;
        }

    } while (!isValid);

    return value;
}