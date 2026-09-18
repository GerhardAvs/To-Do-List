#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>

class InputValidator{
    private:
        static void clearInputBuffer(void);

    public:
        static int readIntInRange(int minValue, int maxValue);
        static std::string readNonEmptyLine(const std::string& prompt);
};

#endif