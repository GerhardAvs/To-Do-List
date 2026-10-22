#include "TaskList.hpp"

#include <stdexcept>

/**
 * @brief Tells whether an index points to an existing task.
 *
 * @param index Zero-based index to check.
 * @return True when the index is inside the list, false otherwise.
 */
bool TaskList::isValidIndex(int index) const {
    return index >= 0 && index < this->getTaskCount();
}

/**
 * @brief Creates a standard task and stores it at the end of the list.
 *
 * @param title Short name of the task.
 * @param description Detailed text explaining the task.
 * @param status Initial progress state of the task.
 */
void TaskList::addTask(const std::string& title, const std::string& description, TaskStatus status) {
    this->tasks.push_back(std::make_unique<Task>(title, description, status));
}

/**
 * @brief Overload: creates a PriorityTask and stores it at the end of the list.
 *
 * @param title Short name of the task.
 * @param description Detailed text explaining the task.
 * @param status Initial progress state of the task.
 * @param priority Priority level of the task.
 */
void TaskList::addTask(const std::string& title, const std::string& description, TaskStatus status, TaskPriority priority) {
    this->tasks.push_back(std::make_unique<PriorityTask>(title, description, status, priority));
}

/**
 * @brief Overload: creates a TaskWithDate and stores it at the end of the list.
 *
 * @param title Short name of the task.
 * @param description Detailed text explaining the task.
 * @param status Initial progress state of the task.
 * @param day Day of the target due date.
 * @param month Month of the target due date.
 * @param year Year of the target due date.
 * @return True when the date is valid and the task was added, false otherwise.
 */
bool TaskList::addTask(const std::string& title, const std::string& description, TaskStatus status, int day, int month, int year) {
    if (!isValidDate(day, month, year)) {
        return false;
    }

    this->tasks.push_back(std::make_unique<TaskWithDate>(title, description, status, day, month, year));
    return true;
}

/**
 * @brief Checks if the task at the specified index is a PriorityTask.
 *
 * @param index Zero-based index of the task.
 * @return True if the task is a PriorityTask, false otherwise.
 */
bool TaskList::isPriorityTask(int index) const {
    if (!this->isValidIndex(index)) {
        return false;
    }

    return dynamic_cast<const PriorityTask*>(this->tasks[index].get()) != nullptr;
}

/**
 * @brief Checks if the task at the specified index is a TaskWithDate.
 *
 * @param index Zero-based index of the task.
 * @return True if the task is a TaskWithDate, false otherwise.
 */
bool TaskList::isTaskWithDate(int index) const {
    if (!this->isValidIndex(index)) {
        return false;
    }

    return dynamic_cast<const TaskWithDate*>(this->tasks[index].get()) != nullptr;
}

/**
 * @brief Replaces the title of a stored task.
 *
 * @param index Zero-based index of the task.
 * @param title The new title.
 * @return True when the task exists, false otherwise.
 */
bool TaskList::updateTaskTitle(int index, const std::string& title) {
    if (!this->isValidIndex(index)) {
        return false;
    }

    this->tasks[index]->setTitle(title);
    return true;
}

/**
 * @brief Replaces the description of a stored task.
 *
 * @param index Zero-based index of the task.
 * @param description The new description.
 * @return True when the task exists, false otherwise.
 */
bool TaskList::updateTaskDescription(int index, const std::string& description) {
    if (!this->isValidIndex(index)) {
        return false;
    }

    this->tasks[index]->setDescription(description);
    return true;
}

/**
 * @brief Replaces the progress state of a stored task.
 *
 * @param index Zero-based index of the task.
 * @param status The new status.
 * @return True when the task exists, false otherwise.
 */
bool TaskList::updateTaskStatus(int index, TaskStatus status) {
    if (!this->isValidIndex(index)) {
        return false;
    }

    this->tasks[index]->setStatus(status);
    return true;
}

/**
 * @brief Updates the priority level of a PriorityTask.
 *
 * @param index Zero-based index of the task.
 * @param priority The new priority level.
 * @return True if the task exists and is a PriorityTask, false otherwise.
 */
bool TaskList::updateTaskPriority(int index, TaskPriority priority) {
    if (!this->isValidIndex(index)) {
        return false;
    }

    auto* task = dynamic_cast<PriorityTask*>(this->tasks[index].get());

    if (task == nullptr) {
        return false;
    }

    task->setPriority(priority);
    return true;
}

/**
 * @brief Updates the target due date of a TaskWithDate.
 *
 * @param index Zero-based index of the task.
 * @param day Day of the target date.
 * @param month Month of the target date.
 * @param year Year of the target date.
 * @return True if the task exists, is a TaskWithDate and the date is valid.
 */
bool TaskList::updateTaskDate(int index, int day, int month, int year) {
    if (!this->isValidIndex(index)) {
        return false;
    }

    auto* task = dynamic_cast<TaskWithDate*>(this->tasks[index].get());

    if (task == nullptr) {
        return false;
    }

    try {
        task->setDate(day, month, year);
    } catch (const std::invalid_argument&) {
        return false;
    }

    return true;
}

/**
 * @brief Removes a task from the list.
 *
 * @param index Zero-based index of the task.
 * @return True when the task exists, false otherwise.
 */
bool TaskList::deleteTask(int index) {
    if (!this->isValidIndex(index)) {
        return false;
    }

    this->tasks.erase(this->tasks.begin() + index);
    return true;
}

/**
 * @brief Tells whether the list holds no tasks.
 *
 * @return True when there are no tasks stored.
 */
bool TaskList::isEmpty() const {
    return this->tasks.empty();
}

/**
 * @brief Gets how many tasks are stored.
 *
 * @return The amount of tasks in the list.
 */
int TaskList::getTaskCount() const {
    return static_cast<int>(this->tasks.size());
}

/**
 * @brief Gets read-only access to the stored tasks.
 *
 * @return Constant reference to the internal vector of tasks.
 */
const std::vector<std::unique_ptr<Task>>& TaskList::getTasks() const {
    return this->tasks;
}