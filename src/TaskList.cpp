#include "TaskList.hpp"

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
 * @brief Creates a task and stores it at the end of the list.
 *
 * @param title       Short name of the task.
 * @param description Detailed text explaining the task.
 * @param status      Initial progress state of the task.
 */
void TaskList::addTask(const std::string& title, const std::string& description, TaskStatus status) {
    this->tasks.push_back(Task(title, description, status));
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

    this->tasks[index].setTitle(title);
    return true;
}

/**
 * @brief Replaces the description of a stored task.
 *
 * @param index       Zero-based index of the task.
 * @param description The new description.
 * @return True when the task exists, false otherwise.
 */
bool TaskList::updateTaskDescription(int index, const std::string& description) {
    if (!this->isValidIndex(index)) {
        return false;
    }

    this->tasks[index].setDescription(description);
    return true;
}

/**
 * @brief Replaces the progress state of a stored task.
 *
 * @param index  Zero-based index of the task.
 * @param status The new status.
 * @return True when the task exists, false otherwise.
 */
bool TaskList::updateTaskStatus(int index, TaskStatus status) {
    if (!this->isValidIndex(index)) {
        return false;
    }

    this->tasks[index].setStatus(status);
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
const std::vector<Task>& TaskList::getTasks() const {
    return this->tasks;
}