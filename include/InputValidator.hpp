#ifndef INPUT_VALIDATOR_HPP
#define INPUT_VALIDATOR_HPP

#include <stdexcept>
#include <string>

/**
 * @brief Thrown when the input stream is closed (EOF, e.g. Ctrl+D / Ctrl+Z).
 *
 * Lets the program leave cleanly instead of looping forever asking for data.
 */
class InputClosedError : public std::runtime_error {
public:
    InputClosedError();
};

/**
 * @brief Console input helpers that never return invalid data.
 */
class InputValidator {
private:
    /**
     * @brief Removes spaces and tabs from both ends of a text.
     *
     * @param text Text to clean.
     * @return The text without surrounding whitespace.
     */
    static std::string trim(const std::string& text);

    /**
     * @brief Tries to convert a whole line into an integer.
     *
     * @param text Line typed by the user.
     * @param value Receives the number when the conversion succeeds.
     * @return True only when the full line is a valid integer.
     */
    static bool tryParseInt(const std::string& text, int& value);

public:
    static int readIntInRange(int minValue, int maxValue);
    static std::string readNonEmptyLine(const std::string& prompt);
    static std::string readLine(const std::string& prompt);
};

#endif  // INPUT_VALIDATOR_HPP