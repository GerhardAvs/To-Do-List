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
            std::cout << ">> Invalid input. Please enter a number." << std::endl;
        }
        else if (value < minValue || value > maxValue)
        {
            std::cout << ">> Option out of range. Please try again." << std::endl;
        }
        else
        {
            isValid = true;
        }

        clearInputBuffer();   // <- siempre, incluso al leer bien

    } while (!isValid);

    return value;
}

/**
 * @brief Reads a whole line of text, rejecting empty input.
 *
 * @param prompt Text shown to the user before reading.
 * @return The line entered by the user.
 */
std::string InputValidator::readNonEmptyLine(const std::string& prompt) {
    std::string line;

    do
    {
        std::cout << prompt;
        std::getline(std::cin, line);

        if (line.empty())
        {
            std::cout << ">> Text cannot be empty. Please try again." << std::endl;
        }

    } while (line.empty());

    return line;
}
