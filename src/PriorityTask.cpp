#include "PriorityTask.hpp"

#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace {
/**
 * @brief Converts text such as "high" or "alta" into a TaskPriority.
 *
 * Accepts English and Spanish names, ignoring case and surrounding spaces.
 *
 * @param level Text typed by the user.
 * @return Matching TaskPriority.
 * @throws std::invalid_argument If the text is not a known priority.
 */
TaskPriority stringToPriority(const std::string& level) {
    std::string text = level;
    text.erase(text.begin(), std::find_if(text.begin(), text.end(),
        [](unsigned char c) { return !std::isspace(c); }));
    text.erase(std::find_if(text.rbegin(), text.rend(),
        [](unsigned char c) { return !std::isspace(c); }).base(), text.end());
    std::transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    if (text == "low" || text == "baja")     return TaskPriority::Low;
    if (text == "medium" || text == "media") return TaskPriority::Medium;
    if (text == "high" || text == "alta")    return TaskPriority::High;

    throw std::invalid_argument("Invalid priority: \"" + level + "\"");
}
}  // namespace

/**
 * @brief Constructs a PriorityTask with all of its fields.
 *
 * @param title Short name of the task.
 * @param description Detailed description of the task.
 * @param status Initial progress state.
 * @param priority Task priority level (Low, Medium, High).
 */
PriorityTask::PriorityTask(const std::string& title, const std::string& description, TaskStatus status, TaskPriority priority)
    : Task(title, description, status), priority(priority) {}

/**
 * @brief Overload: constructs a Pending task with the given priority.
 *
 * @param title Short name of the task.
 * @param description Detailed description of the task.
 * @param priority Task priority level (Low, Medium, High).
 */
PriorityTask::PriorityTask(const std::string& title, const std::string& description, TaskPriority priority)
    : PriorityTask(title, description, TaskStatus::Pending, priority) {}

/**
 * @brief Overload: constructs a Pending task with Medium priority.
 *
 * @param title Short name of the task.
 * @param description Detailed description of the task.
 */
PriorityTask::PriorityTask(const std::string& title, const std::string& description)
    : PriorityTask(title, description, TaskStatus::Pending, TaskPriority::Medium) {}

/**
 * @brief Gets the priority of the task.
 *
 * @return Current priority level.
 */
TaskPriority PriorityTask::getPriority() const {
    return this->priority;
}

/**
 * @brief Sets the priority from a TaskPriority value.
 *
 * @param priority New priority level.
 */
void PriorityTask::setPriority(TaskPriority priority) {
    this->priority = priority;
}

/**
 * @brief Overload: sets the priority from text typed by the user.
 *
 * @param level "low", "medium" or "high" (also "baja", "media", "alta").
 * @throws std::invalid_argument If the text is not a known priority.
 */
void PriorityTask::setPriority(const std::string& level) {
    this->priority = stringToPriority(level);
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

/**
 * @brief Converts a priority into its display name.
 *
 * @param priority Priority level to convert.
 * @return "Low", "Medium", "High" or "Unknown".
 */
std::string priorityToString(TaskPriority priority) {
    switch (priority) {
        case TaskPriority::Low:    return "Low";
        case TaskPriority::Medium: return "Medium";
        case TaskPriority::High:   return "High";
        default:                   return "Unknown";
    }
}