#include "TaskWithDate.hpp"

#include <iomanip>
#include <sstream>

/**
 * @brief Constructs a task with a validated target date.
 *
 * @param title Short name of the task.
 * @param description Detailed text.
 * @param status Initial progress state.
 * @param day Day of the target date.
 * @param month Month of the target date.
 * @param year Year of the target date.
 */
TaskWithDate::TaskWithDate(
    const std::string& title,
    const std::string& description,
    TaskStatus status,
    int day,
    int month,
    int year
)
    : Task(title, description, status) {
    setDate(day, month, year);
}

/**
 * @brief Calculates the number of days in a month, including leap years.
 *
 * @param month Month value from 1 to 12.
 * @param year Year value.
 * @return Number of days in the specified month.
 */
int daysInMonth(int month, int year) {
    if (month == 2) {
        const bool isLeapYear =
            year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);

        return isLeapYear ? 29 : 28;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }

    return 31;
}

/**
 * @brief Validates and stores a target date.
 *
 * @param day Day value.
 * @param month Month value.
 * @param year Year value.
 */
void TaskWithDate::setDate(int day, int month, int year) {
    this->year = year;

    if (this->year < minYear || this->year > maxYear) {
        this->year = minYear;
    }

    this->month = month;

    if (this->month < 1 || this->month > 12) {
        this->month = 1;
    }

    const int lastDay = daysInMonth(this->month, this->year);
    this->day = day;

    if (this->day < 1 || this->day > lastDay) {
        this->day = 1;
    }
}

/**
 * @brief Formats the target date as YYYY-MM-DD.
 *
 * @return Formatted target date.
 */
std::string TaskWithDate::getDate() const {
    std::ostringstream oss;

    oss << std::setfill('0') << std::setw(4) << this->year << "-"
        << std::setw(2) << this->month << "-"
        << std::setw(2) << this->day;

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
