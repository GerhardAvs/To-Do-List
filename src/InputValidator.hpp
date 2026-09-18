#ifndef INPUT_VALIDATOR_HPP
#define INPUT_VALIDATOR_HPP

#include <string>

/**
 * @brief Console input helpers that never return invalid data.
 */
class InputValidator {
private:
    static void clearInputBuffer();

public:
    static int readIntInRange(int minValue, int maxValue);
    static std::string readNonEmptyLine(const std::string& prompt);
    static std::string readLine(const std::string& prompt);
};

#endif