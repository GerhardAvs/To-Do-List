#ifndef PRIORITYTASK_HPP
#define PRIORITYTASK_HPP

#include "Task.hpp"
#include "string"

enum class TaskPriority{
    Low = 1,
    Medium = 2,
    High = 3
};

class PriorityTask : public Task {
    private:
        TaskPriority priority;
    public:
        PriorityTask(const std::string& title, const std::string& description, TaskStatus status,  TaskPriority priority);

        TaskPriority getPriority() const;
        void setPriority(TaskPriority priority);
};

std::string priorityToString(TaskPriority priority);
TaskPriority priorityFromInt(int value);


#endif