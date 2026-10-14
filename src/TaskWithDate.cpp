#include "TaskWithDate.hpp"
#include <iomanip>
#include <sstream>

TaskWithDate::TaskWithDate(const std::string& title, const std::string& description, TaskStatus status, int day, int month, int year)
    : Task(title, description, status) {
    setDate(day, month, year);
}

int TaskWithDate::daysInMonth(int month, int year) const {
    if (month == 2) {
        bool leapYear = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
        return leapYear ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

void TaskWithDate::setDate(int d, int m, int y) {
    this->year = (y >= 2000) ? y : 2026;
    this->month = (m >= 1 && m <= 12) ? m : 1;

    int maxDays = daysInMonth(this->month, this->year);
    this->day = (d >= 1 && d <= maxDays) ? d : 1;
}

std::string TaskWithDate::getDate() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << year << "-"
        << std::setw(2) << month << "-"
        << std::setw(2) << day;
    return oss.str();
}

/**
 * @brief Appends date information to the output stream.
 * 
 * @param os Output stream to write to.
 */
void TaskWithDate::printDetails(std::ostream& os) const {
    Task::printDetails(os);
    os << " | Due Date: " << getDate();
}