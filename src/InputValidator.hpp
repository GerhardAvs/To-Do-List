#ifndef INPUT_HPP
#define INPUT_HPP

class InputValidator{
    private:
        static void clearInputBuffer(void);

    public:
        static int readIntInRange(int minValue, int maxValue);
};

#endif