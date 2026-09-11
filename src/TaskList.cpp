#include "TaskList.hpp"

void TaskList::addTask(const std::string& description, TaskStatus status) {
    this->tasks.push_back(Task(description, status));
}

bool TaskList::updateTaskStatus(int position, TaskStatus status) {
    if (position < 0 || position >= this->getTaskCount()) {
        return false;
    }

    this->tasks[position].setStatus(status);
    return true;
}

bool TaskList::deleteTask(int position) {
    if (position < 0 || position >= this->getTaskCount()) {
        return false;
    }

    this->tasks.erase(this->tasks.begin() + position);
    return true;
}

int TaskList::getTaskCount() const {
    return static_cast<int>(this->tasks.size());
}

const std::vector<Task>& TaskList::getTasks() const {
    return this->tasks;
}
