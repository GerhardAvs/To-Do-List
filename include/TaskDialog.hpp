#ifndef TASK_DIALOG_HPP
#define TASK_DIALOG_HPP

#include "Task.hpp"

#include <QDialog>

#include <memory>

class QComboBox;
class QDateEdit;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPlainTextEdit;

/**
 * @brief Small window used to capture a new task or edit an existing one.
 *
 * It inherits from QDialog and overrides the virtual accept() so the window
 * only closes when the typed data is valid.
 *
 * Create mode:  TaskDialog dialog(this);
 *               if (dialog.exec() == QDialog::Accepted) { auto task = dialog.takeTask(); }
 *
 * Edit mode:    TaskDialog dialog(existingTask, this);
 *               if (dialog.exec() == QDialog::Accepted) { dialog.applyTo(existingTask); }
 */
class TaskDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Builds an empty dialog to create a task of any type.
     *
     * @param parent Parent window (usually MainWindow).
     */
    explicit TaskDialog(QWidget* parent = nullptr);

    /**
     * @brief Overload: builds the dialog filled with an existing task to edit it.
     *
     * The task type cannot be changed while editing.
     *
     * @param task Task whose data is shown.
     * @param parent Parent window (usually MainWindow).
     */
    explicit TaskDialog(const Task& task, QWidget* parent = nullptr);

    /**
     * @brief Gives the task created when the user pressed OK.
     *
     * @return The new task (Task, PriorityTask or TaskWithDate), or nullptr if
     *         the dialog was cancelled or the method was already called.
     */
    std::unique_ptr<Task> takeTask();

    /**
     * @brief Copies the validated data into an existing task (edit mode).
     *
     * Keeps the original creation date.
     *
     * @param task Task to update. Its type must match the type shown in the dialog.
     */
    void applyTo(Task& task) const;

protected:
    /**
     * @brief Overrides QDialog::accept(): validates before closing.
     *
     * If something is wrong it shows a warning and the dialog stays open.
     */
    void accept() override;

private slots:
    /**
     * @brief Shows or hides the extra fields for the selected task type.
     *
     * @param index Index selected in the type combo box.
     */
    void onTypeChanged(int index);

private:
    QComboBox* typeCombo = nullptr;
    QLineEdit* titleEdit = nullptr;
    QPlainTextEdit* descriptionEdit = nullptr;
    QComboBox* statusCombo = nullptr;
    QLabel* priorityLabel = nullptr;
    QComboBox* priorityCombo = nullptr;
    QLabel* dateLabel = nullptr;
    QDateEdit* dateEdit = nullptr;
    QDialogButtonBox* buttons = nullptr;

    std::unique_ptr<Task> createdTask;

    /**
     * @brief Creates the widgets and the layout. Shared by both constructors.
     */
    void buildUi();

    /**
     * @brief Builds the task from the current fields.
     *
     * @return The new task.
     * @throws std::invalid_argument If any value is not valid.
     */
    std::unique_ptr<Task> buildTaskFromFields() const;
};

#endif  // TASK_DIALOG_HPP
