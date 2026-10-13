#ifndef TASK_WITH_DATE_HPP
#define TASK_WITH_DATE_HPP

#include "Task.hpp"
#include <string>

class TaskWithDate : public Task {
private:
    int day;
    int month;
    int year;

protected:
    int daysInMonth(int month, int year) const;

public:
    TaskWithDate();

    void setDate(int day, int month, int year);
    void inputDate();
    std::string getDate() const;
};

#endif
