#include "PriorityTask.hpp"

PriorityTask::PriorityTask(const std::string& title, const std::string& description, TaskStatus status,  TaskPriority priority)
   :Task(title, description, status),
    priority(priority){
}

TaskPriority PriorityTask::getPriority() const{
    return this->priority;
}

void PriorityTask::setPriority(TaskPriority priority){
    this->priority = priority;
}

std::string priorityToString(TaskPriority priority){
    if (priority == TaskPriority::Low) {
        return "Low";
    }

    if (priority == TaskPriority::Medium) {
        return "Medium";
    }

    return "High";
}

TaskPriority priorityFromInt(int value){
    if (value == static_cast<int>(TaskPriority::Low)) {
        return TaskPriority::Low;
    }

    if (value == static_cast<int>(TaskPriority::Medium)) {
        return TaskPriority::Medium;
    }

    return TaskPriority::High;
}