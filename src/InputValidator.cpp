#import <iostream>
#import <limits>

#import  "InputValidator.hpp"

void InputValidator::clearInputBuffer(void){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

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