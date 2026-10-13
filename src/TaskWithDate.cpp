#include "TaskWithDate.hpp"
#include "InputValidator.hpp"

#include <iostream>
#include <string>

//Constructor
TaskWithDate::TaskWithDate(){
    day = 1;
    month = 1;
    year = 2026;
}

//Calculate the numbers of days in a month
int TaskWithDate::daysInMonth(int month, int year) const {
    if (month == 2){
        bool leapYear = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);

        return leapYear ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11 ){
        return 30;
    }

    return 31;
}

//Guarda una fecha valida
void TaskWithDate::setDate(int d, int m, int y){
    //still coding
}

void TaskWithDate::inputDate(){
    //still coding
}
