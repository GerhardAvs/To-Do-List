#include "MainWindow.hpp"

#include "TaskDialog.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>

#include <memory>
#include <string>

/**
 * @brief Builds the window with the task list and its buttons.
 *
 * @param parent Parent widget.
 */
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    this->buildUi();
    this->refreshList();
}

/**
 * @brief Creates the widgets, the layout and the signal connections.
 */
void MainWindow::buildUi() {
    this->setWindowTitle(tr("C++ To Do List Manager"));
    this->resize(640, 480);

    auto* central = new QWidget(this);

    this->taskListWidget = new QListWidget(central);
    this->taskListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    this->taskListWidget->setAlternatingRowColors(true);
    this->taskListWidget->setWordWrap(true);

    this->emptyLabel = new QLabel(tr("No tasks yet. Press \"Add\" to create one."), central);
    this->emptyLabel->setAlignment(Qt::AlignCenter);

    this->addButton = new QPushButton(tr("Add"), central);
    this->toggleStatusButton = new QPushButton(tr("Change status"), central);
    this->deleteButton = new QPushButton(tr("Delete"), central);

    auto* buttonRow = new QHBoxLayout();
    buttonRow->addWidget(this->addButton);
    buttonRow->addWidget(this->toggleStatusButton);
    buttonRow->addWidget(this->deleteButton);
    buttonRow->addStretch();

    auto* layout = new QVBoxLayout(central);
    layout->addWidget(this->taskListWidget);
    layout->addWidget(this->emptyLabel);
    layout->addLayout(buttonRow);

    this->setCentralWidget(central);

    connect(this->addButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(this->toggleStatusButton, &QPushButton::clicked, this, &MainWindow::toggleStatus);
    connect(this->deleteButton, &QPushButton::clicked, this, &MainWindow::deleteTask);
    connect(this->taskListWidget, &QListWidget::currentRowChanged, this, &MainWindow::updateButtons);
}

/**
 * @brief Clears the list widget and fills it again from the TaskList.
 *
 * Each row is built only with virtual methods: getTypeName() and toString()
 * run the version of the real type (Task, PriorityTask or TaskWithDate).
 */
void MainWindow::refreshList() {
    const int previousRow = this->taskListWidget->currentRow();

    this->taskListWidget->clear();

    int number = 1;
    for (const auto& task : this->taskList.getTasks()) {
        const std::string text =
            "[" + std::to_string(number) + "] " + task->getTitle() +
            "  (" + task->getTypeName() + ")\n" + task->toString();

        this->taskListWidget->addItem(QString::fromStdString(text));
        ++number;
    }

    const int count = this->taskList.getTaskCount();
    if (count > 0) {
        this->taskListWidget->setCurrentRow(previousRow < count ? previousRow : count - 1);
    }

    this->taskListWidget->setVisible(count > 0);
    this->emptyLabel->setVisible(count == 0);
    this->statusBar()->showMessage(tr("%n task(s)", "", count));

    this->updateButtons();
}

/**
 * @brief Opens TaskDialog and stores the new task when the user presses OK.
 */
void MainWindow::addTask() {
    TaskDialog dialog(this);

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    if (this->taskList.addTask(dialog.takeTask())) {
        this->refreshList();
        this->taskListWidget->setCurrentRow(this->taskList.getTaskCount() - 1);
    }
}

/**
 * @brief Marks the selected task as completed, or as pending if it was completed.
 */
void MainWindow::toggleStatus() {
    Task* task = this->taskList.getTask(this->selectedIndex());

    if (task == nullptr) {
        return;
    }

    const TaskStatus newStatus =
        task->getStatus() == TaskStatus::Completed ? TaskStatus::Pending : TaskStatus::Completed;

    this->taskList.updateTaskStatus(this->selectedIndex(), newStatus);
    this->refreshList();
}

/**
 * @brief Deletes the selected task after asking for confirmation.
 */
void MainWindow::deleteTask() {
    const int index = this->selectedIndex();
    const Task* task = this->taskList.getTask(index);

    if (task == nullptr) {
        return;
    }

    const auto answer = QMessageBox::question(
        this,
        tr("Delete task"),
        tr("Delete \"%1\"?").arg(QString::fromStdString(task->getTitle())));

    if (answer != QMessageBox::Yes) {
        return;
    }

    this->taskList.deleteTask(index);
    this->refreshList();
}

/**
 * @brief Enables the buttons that need a selected task only when there is one.
 */
void MainWindow::updateButtons() {
    const bool hasSelection = this->selectedIndex() >= 0;

    this->toggleStatusButton->setEnabled(hasSelection);
    this->deleteButton->setEnabled(hasSelection);
}

/**
 * @brief Gets the row selected in the list.
 *
 * @return Zero-based index of the selected task, or -1 when nothing is selected.
 */
int MainWindow::selectedIndex() const {
    const int row = this->taskListWidget->currentRow();

    return row < this->taskList.getTaskCount() ? row : -1;
}
