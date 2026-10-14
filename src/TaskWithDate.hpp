#ifndef TASK_WITH_DATE_HPP
#define TASK_WITH_DATE_HPP

#include "Task.hpp"
#include <string>

/**
 * @brief Derived class representing a task that has a specific target date.
 */
class TaskWithDate : public Task {
private:
    int day;
    int month;
    int year;

protected:
    /**
     * @brief Calculates the total number of days in a given month.
     * 
     * @param month Month value (1 to 12).
     * @param year Year value.
     * @return Number of days in the specified month.
     */
    int daysInMonth(int month, int year) const;

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
     */
    TaskWithDate(const std::string& title, const std::string& description, TaskStatus status, int day, int month, int year);

    /**
     * @brief Validates and stores a new target date.
     * 
     * @param day Day value.
     * @param month Month value.
     * @param year Year value.
     */
    void setDate(int day, int month, int year);

    /**
     * @brief Formats the date into a YYYY-MM-DD string.
     * 
     * @return Formatted date string.
     */
    std::string getDate() const;

    /**
     * @brief Prints task details including the target due date.
     * 
     * @param os Output stream to write to.
     */
    void printDetails(std::ostream& os = std::cout) const override;
};

#endif