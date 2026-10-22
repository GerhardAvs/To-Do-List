#include "TaskWithDate.hpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>

/**
 * @brief Constructs a task with a validated target date.
 *
 * @param title Short name of the task.
 * @param description Detailed text.
 * @param status Initial progress state.
 * @param day Day of the target date.
 * @param month Month of the target date.
 * @param year Year of the target date.
 * @throws std::invalid_argument If the date is not valid.
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
    this->setDate(day, month, year);
}

/**
 * @brief Overload: constructs a Pending task with a target date.
 *
 * @param title Short name of the task.
 * @param description Detailed text.
 * @param day Day of the target date.
 * @param month Month of the target date.
 * @param year Year of the target date.
 * @throws std::invalid_argument If the date is not valid.
 */
TaskWithDate::TaskWithDate(
    const std::string& title,
    const std::string& description,
    int day,
    int month,
    int year
)
    : TaskWithDate(title, description, TaskStatus::Pending, day, month, year) {
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
 * @brief Tells whether a day, month and year form a valid due date.
 *
 * @param day Day value.
 * @param month Month value.
 * @param year Year value.
 * @return True when the date exists and is inside the accepted range.
 */
bool isValidDate(int day, int month, int year) {
    if (year < minYear || year > maxYear) {
        return false;
    }

    if (month < 1 || month > monthsPerYear) {
        return false;
    }

    return day >= 1 && day <= daysInMonth(month, year);
}

/**
 * @brief Validates and stores a target date.
 *
 * @param day Day value.
 * @param month Month value.
 * @param year Year value.
 * @throws std::invalid_argument If the date is not valid.
 */
void TaskWithDate::setDate(int day, int month, int year) {
    if (!isValidDate(day, month, year)) {
        throw std::invalid_argument("Invalid due date.");
    }

    this->day = day;
    this->month = month;
    this->year = year;
}

/**
 * @brief Gets the day of the due date.
 *
 * @return Day value.
 */
int TaskWithDate::getDay() const {
    return this->day;
}

/**
 * @brief Gets the month of the due date.
 *
 * @return Month value.
 */
int TaskWithDate::getMonth() const {
    return this->month;
}

/**
 * @brief Gets the year of the due date.
 *
 * @return Year value.
 */
int TaskWithDate::getYear() const {
    return this->year;
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
 * @brief Names the kind of task.
 *
 * @return "With due date".
 */
std::string TaskWithDate::getTypeName() const {
    return "With due date";
}

/**
 * @brief Appends date information to the output stream.
 *
 * @param os Output stream to write to.
 */
void TaskWithDate::printDetails(std::ostream& os) const {
    Task::printDetails(os);
    os << " | Due Date: " << this->getDate();
}