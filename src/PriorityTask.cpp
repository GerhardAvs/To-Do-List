#include "PriorityTask.hpp"

PriorityTask::PriorityTask(const std::string& title, const std::string& description, TaskStatus status, TaskPriority priority)
    : Task(title, description, status), priority(priority) {}

TaskPriority PriorityTask::getPriority() const {
    return this->priority;
}

void PriorityTask::setPriority(TaskPriority priority) {
    this->priority = priority;
}

/**
 * @brief Appends priority details to the output stream.
 * 
 * @param os Output stream to write to.
 */
void PriorityTask::printDetails(std::ostream& os) const {
    Task::printDetails(os);
    os << " | Priority: " << priorityToString(this->priority);
}

std::string priorityToString(TaskPriority priority) {
    switch (priority) {
        case TaskPriority::Low:    return "Low";
        case TaskPriority::Medium: return "Medium";
        case TaskPriority::High:   return "High";
        default:                   return "Unknown";
    }
}