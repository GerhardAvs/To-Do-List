#include "InputValidator.hpp"

#include <iostream>
#include <limits>

/**
 * @brief Discards the rest of the current input line.
 */
void InputValidator::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Reads an integer, asking again until it falls inside the given range.
 *
 * @param minValue Minimum accepted value.
 * @param maxValue Maximum accepted value.
 * @return The validated value entered by the user.
 */
int InputValidator::readIntInRange(int minValue, int maxValue) {
    int value = 0;
    bool isValid = false;

    do {
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << ">> Invalid input. Please enter a number." << std::endl;
        } else if (value < minValue || value > maxValue) {
            std::cout << ">> Value out of range. Please try again." << std::endl;
        } else {
            isValid = true;
        }

        clearInputBuffer();
    } while (!isValid);

    return value;
}

/**
 * @brief Reads a whole line, asking again while the user submits empty text.
 *
 * @param prompt Text shown before reading.
 * @return The non-empty line entered by the user.
 */
std::string InputValidator::readNonEmptyLine(const std::string& prompt) {
    std::string line;

    do {
        line = readLine(prompt);

        if (line.empty()) {
            std::cout << ">> Text cannot be empty. Please try again." << std::endl;
        }
    } while (line.empty());

    return line;
}

/**
 * @brief Reads a whole line and accepts empty text.
 *
 * @param prompt Text shown before reading.
 * @return The line entered by the user, possibly empty.
 */
std::string InputValidator::readLine(const std::string& prompt) {
    std::string line;

    std::cout << prompt;
    std::getline(std::cin, line);

    return line;
}