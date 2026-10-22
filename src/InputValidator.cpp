#include "InputValidator.hpp"

#include <iostream>
#include <stdexcept>

/**
 * @brief Builds the error with a descriptive message.
 */
InputClosedError::InputClosedError()
    : std::runtime_error("Input stream was closed.") {
}

/**
 * @brief Removes spaces and tabs from both ends of a text.
 *
 * @param text Text to clean.
 * @return The text without surrounding whitespace.
 */
std::string InputValidator::trim(const std::string& text) {
    const std::string whitespace = " \t\r\n";
    const std::size_t first = text.find_first_not_of(whitespace);

    if (first == std::string::npos) {
        return "";
    }

    const std::size_t last = text.find_last_not_of(whitespace);
    return text.substr(first, last - first + 1);
}

/**
 * @brief Tries to convert a whole line into an integer.
 *
 * Rejects mixed input such as "3abc" or "2 5" instead of silently keeping
 * the first number.
 *
 * @param text Line typed by the user.
 * @param value Receives the number when the conversion succeeds.
 * @return True only when the full line is a valid integer.
 */
bool InputValidator::tryParseInt(const std::string& text, int& value) {
    if (text.empty()) {
        return false;
    }

    try {
        std::size_t consumed = 0;
        const int parsed = std::stoi(text, &consumed);

        if (consumed != text.size()) {
            return false;
        }

        value = parsed;
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

/**
 * @brief Reads an integer, asking again until it falls inside the given range.
 *
 * @param minValue Minimum accepted value.
 * @param maxValue Maximum accepted value.
 * @return The validated value entered by the user.
 * @throws InputClosedError If the input stream reaches EOF.
 */
int InputValidator::readIntInRange(int minValue, int maxValue) {
    int value = 0;

    while (true) {
        const std::string line = readLine("");

        if (!tryParseInt(line, value)) {
            std::cout << ">> Invalid input. Please enter a number: ";
        } else if (value < minValue || value > maxValue) {
            std::cout << ">> Value out of range (" << minValue << "-" << maxValue
                      << "). Please try again: ";
        } else {
            return value;
        }
    }
}

/**
 * @brief Reads a whole line, asking again while the user submits empty text.
 *
 * Text made only of spaces is treated as empty.
 *
 * @param prompt Text shown before reading.
 * @return The non-empty line entered by the user.
 * @throws InputClosedError If the input stream reaches EOF.
 */
std::string InputValidator::readNonEmptyLine(const std::string& prompt) {
    std::string line = readLine(prompt);

    while (line.empty()) {
        std::cout << ">> Text cannot be empty. Please try again." << std::endl;
        line = readLine(prompt);
    }

    return line;
}

/**
 * @brief Reads a whole line and accepts empty text.
 *
 * Surrounding spaces are removed, so "   " counts as an empty answer.
 *
 * @param prompt Text shown before reading.
 * @return The line entered by the user, possibly empty.
 * @throws InputClosedError If the input stream reaches EOF.
 */
std::string InputValidator::readLine(const std::string& prompt) {
    std::string line;

    std::cout << prompt;

    if (!std::getline(std::cin, line)) {
        throw InputClosedError();
    }

    return trim(line);
}