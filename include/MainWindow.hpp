#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "TaskList.hpp"

#include <QMainWindow>

class QLabel;
class QListWidget;
class QPushButton;

/**
 * @brief Main screen of the application. Shows every task of every type.
 *
 * It inherits from QMainWindow. Each task is shown through its virtual
 * methods (getTypeName() and toString()), so the window never checks the
 * task type with if or switch: polymorphism picks the right text.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Builds the window with the task list and its buttons.
     *
     * @param parent Parent widget (normally nullptr for the main window).
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /**
     * @brief Clears the list widget and fills it again from the TaskList.
     *
     * Called after every change so the screen always matches the data.
     */
    void refreshList();

private slots:
    /**
     * @brief Opens TaskDialog and stores the new task when the user presses OK.
     */
    void addTask();

    /**
     * @brief Marks the selected task as completed, or as pending if it was completed.
     */
    void toggleStatus();

    /**
     * @brief Deletes the selected task after asking for confirmation.
     */
    void deleteTask();

    /**
     * @brief Enables the buttons that need a selected task only when there is one.
     */
    void updateButtons();

private:
    TaskList taskList;

    QListWidget* taskListWidget = nullptr;
    QPushButton* addButton = nullptr;
    QPushButton* toggleStatusButton = nullptr;
    QPushButton* deleteButton = nullptr;
    QLabel* emptyLabel = nullptr;

    /**
     * @brief Creates the widgets, the layout and the signal connections.
     */
    void buildUi();

    /**
     * @brief Gets the row selected in the list.
     *
     * @return Zero-based index of the selected task, or -1 when nothing is selected.
     */
    int selectedIndex() const;
};

#endif  // MAIN_WINDOW_HPP
