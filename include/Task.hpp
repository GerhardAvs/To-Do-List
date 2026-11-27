#ifndef TASK_HPP
#define TASK_HPP

#include <iosfwd>
#include <string>

/**
 * @brief Progress state a task can be in.
 */
enum class TaskStatus {
    Pending = 1,
    InProgress = 2,
    Completed = 3
};

/** @brief Amount of values declared in TaskStatus. */
constexpr int taskStatusCount = 3;

/**
 * @brief Base class representing a single to-do entry.
 */
class Task {
private:
    std::string title;
    std::string description;
    TaskStatus status;
    std::string creationDate;
    int id = -1;

public:
    /**
     * @brief Constructs a base Task with title, description, and status.
     *
     * @param title Short name of the task.
     * @param description Detailed text explaining the task.
     * @param status Initial progress state of the task.
     */
    Task(const std::string& title, const std::string& description, TaskStatus status);

    /**
     * @brief Overload: constructs a Pending task.
     *
     * @param title Short name of the task.
     * @param description Detailed text explaining the task.
     */
    Task(const std::string& title, const std::string& description);

    /**
     * @brief Virtual destructor for polymorphic cleanup.
     */
    virtual ~Task() = default;

    const std::string& getTitle() const;
    const std::string& getDescription() const;
    TaskStatus getStatus() const;
    const std::string& getCreationDate() const;

    /**
     * @brief Gets the database id of the task.
     *
     * @return Row id in the tasks table, or -1 while the task is not saved yet.
     */
    int getId() const;

    /**
     * @brief Stores the database id of the task (set by saveTask() and loadTasks()).
     *
     * @param id Row id in the tasks table.
     */
    void setId(int id);

    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setStatus(TaskStatus status);

    /**
     * @brief Polymorphic function that names the kind of task.
     *
     * @return "Normal" for the base class; derived classes override it.
     */
    virtual std::string getTypeName() const;

    /**
     * @brief Stable identifier of the task type, used to save it in the database.
     *
     * @return "normal" for the base class; derived classes override it.
     */
    virtual std::string getType() const;

    /**
     * @brief Builds the detailed text of the task, ready to be shown by any interface.
     *
     * The model never prints: the console or the Qt window decide where to show it.
     *
     * @return Description, status and creation date; derived classes append their fields.
     */
    virtual std::string toString() const;
};

/**
 * @brief Operator overload: prints any task (base or derived) with <<.
 *
 * Writes the virtual toString(), so the derived version is used.
 *
 * @param os Output stream to write to.
 * @param task Task to print.
 * @return The same stream, to allow chaining.
 */
std::ostream& operator<<(std::ostream& os, const Task& task);

std::string statusToString(TaskStatus status);
TaskStatus statusFromInt(int value);

#endif  // TASK_HPP