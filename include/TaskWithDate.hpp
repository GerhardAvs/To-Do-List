#ifndef TASK_WITH_DATE_HPP
#define TASK_WITH_DATE_HPP

#include "Task.hpp"

#include <string>

/** @brief Earliest year accepted for a task due date. */
constexpr int minYear = 2024;

/** @brief Latest year accepted for a task due date. */
constexpr int maxYear = 2100;

/** @brief Amount of months in a year. */
constexpr int monthsPerYear = 12;

/**
 * @brief Derived class representing a task that has a specific target date.
 */
class TaskWithDate : public Task {
private:
    int day = 1;
    int month = 1;
    int year = minYear;

public:
    /**
     * @brief Constructs a TaskWithDate object.
     *
     * @param title Short name of the task.
     * @param description Detailed text.
     * @param status Initial progress state.
     * @param day Day of the target date.
     * @param month Month of the target date.
     * @param year Year of the target date.
     * @throws std::invalid_argument If the date is not valid.
     */
    TaskWithDate(
        const std::string& title,
        const std::string& description,
        TaskStatus status,
        int day,
        int month,
        int year
    );

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
    TaskWithDate(
        const std::string& title,
        const std::string& description,
        int day,
        int month,
        int year
    );

    /**
     * @brief Validates and stores a new target date.
     *
     * The previous date is kept when the new one is invalid.
     *
     * @param day Day value.
     * @param month Month value.
     * @param year Year value.
     * @throws std::invalid_argument If the date is not valid.
     */
    void setDate(int day, int month, int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    /**
     * @brief Formats the date into a YYYY-MM-DD string.
     *
     * @return Formatted date string.
     */
    std::string getDate() const;

    /**
     * @brief Names the kind of task.
     *
     * @return "With due date".
     */
    std::string getTypeName() const override;

    /**
     * @brief Prints task details including the target due date.
     *
     * @param os Output stream to write to.
     */
    void printDetails(std::ostream& os = std::cout) const override;
};

/**
 * @brief Calculates the total number of days in a given month.
 *
 * @param month Month value from 1 to 12.
 * @param year Year value.
 * @return Number of days in the specified month.
 */
int daysInMonth(int month, int year);

/**
 * @brief Tells whether a day, month and year form a valid due date.
 *
 * @param day Day value.
 * @param month Month value.
 * @param year Year value (between minYear and maxYear).
 * @return True when the date exists and is inside the accepted range.
 */
bool isValidDate(int day, int month, int year);

#endif  // TASK_WITH_DATE_HPP