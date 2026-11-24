#include "TaskDialog.hpp"

#include "PriorityTask.hpp"
#include "TaskWithDate.hpp"

#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>

#include <stdexcept>
#include <utility>

namespace {

/** @brief Values stored in the type combo box (same names as Task::getType()). */
const QString typeNormal = QStringLiteral("normal");
const QString typePriority = QStringLiteral("priority");
const QString typeDate = QStringLiteral("date");

}  // namespace

/**
 * @brief Builds an empty dialog to create a task of any type.
 *
 * @param parent Parent window.
 */
TaskDialog::TaskDialog(QWidget* parent)
    : QDialog(parent) {
    this->buildUi();
    this->setWindowTitle(tr("New task"));
}

/**
 * @brief Overload: builds the dialog filled with an existing task.
 *
 * @param task Task to edit.
 * @param parent Parent window.
 */
TaskDialog::TaskDialog(const Task& task, QWidget* parent)
    : QDialog(parent) {
    this->buildUi();
    this->setWindowTitle(tr("Edit task"));

    const int typeIndex = this->typeCombo->findData(QString::fromStdString(task.getType()));
    this->typeCombo->setCurrentIndex(typeIndex < 0 ? 0 : typeIndex);
    this->typeCombo->setEnabled(false);

    this->titleEdit->setText(QString::fromStdString(task.getTitle()));
    this->descriptionEdit->setPlainText(QString::fromStdString(task.getDescription()));
    this->statusCombo->setCurrentIndex(this->statusCombo->findData(static_cast<int>(task.getStatus())));

    if (const auto* priorityTask = dynamic_cast<const PriorityTask*>(&task)) {
        this->priorityCombo->setCurrentIndex(
            this->priorityCombo->findData(static_cast<int>(priorityTask->getPriority())));
    }

    if (const auto* dateTask = dynamic_cast<const TaskWithDate*>(&task)) {
        this->dateEdit->setDate(QDate(dateTask->getYear(), dateTask->getMonth(), dateTask->getDay()));
    }
}

/**
 * @brief Creates the widgets and the layout.
 */
void TaskDialog::buildUi() {
    this->typeCombo = new QComboBox(this);
    this->typeCombo->addItem(tr("Normal"), typeNormal);
    this->typeCombo->addItem(tr("With priority"), typePriority);
    this->typeCombo->addItem(tr("With due date"), typeDate);

    this->titleEdit = new QLineEdit(this);
    this->titleEdit->setPlaceholderText(tr("Short name of the task"));

    this->descriptionEdit = new QPlainTextEdit(this);
    this->descriptionEdit->setPlaceholderText(tr("Details (optional)"));
    this->descriptionEdit->setMaximumHeight(90);

    this->statusCombo = new QComboBox(this);
    for (int value = 1; value <= taskStatusCount; ++value) {
        this->statusCombo->addItem(QString::fromStdString(statusToString(statusFromInt(value))), value);
    }

    this->priorityLabel = new QLabel(tr("Priority:"), this);
    this->priorityCombo = new QComboBox(this);
    for (int value = 1; value <= taskPriorityCount; ++value) {
        this->priorityCombo->addItem(QString::fromStdString(priorityToString(priorityFromInt(value))), value);
    }
    this->priorityCombo->setCurrentIndex(this->priorityCombo->findData(static_cast<int>(TaskPriority::Medium)));

    this->dateLabel = new QLabel(tr("Due date:"), this);
    this->dateEdit = new QDateEdit(QDate::currentDate(), this);
    this->dateEdit->setCalendarPopup(true);
    this->dateEdit->setDisplayFormat(QStringLiteral("yyyy-MM-dd"));
    this->dateEdit->setMinimumDate(QDate(minYear, 1, 1));
    this->dateEdit->setMaximumDate(QDate(maxYear, 12, 31));

    auto* form = new QFormLayout();
    form->addRow(tr("Type:"), this->typeCombo);
    form->addRow(tr("Title:"), this->titleEdit);
    form->addRow(tr("Description:"), this->descriptionEdit);
    form->addRow(tr("Status:"), this->statusCombo);
    form->addRow(this->priorityLabel, this->priorityCombo);
    form->addRow(this->dateLabel, this->dateEdit);

    this->buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(this->buttons, &QDialogButtonBox::accepted, this, &TaskDialog::accept);
    connect(this->buttons, &QDialogButtonBox::rejected, this, &TaskDialog::reject);

    auto* layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(this->buttons);

    connect(this->typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &TaskDialog::onTypeChanged);
    this->onTypeChanged(this->typeCombo->currentIndex());

    this->setMinimumWidth(380);
}

/**
 * @brief Shows only the fields that belong to the selected type.
 *
 * @param index Index selected in the type combo box.
 */
void TaskDialog::onTypeChanged(int index) {
    const QString type = this->typeCombo->itemData(index).toString();
    const bool showPriority = type == typePriority;
    const bool showDate = type == typeDate;

    this->priorityLabel->setVisible(showPriority);
    this->priorityCombo->setVisible(showPriority);
    this->dateLabel->setVisible(showDate);
    this->dateEdit->setVisible(showDate);

    this->adjustSize();
}

/**
 * @brief Builds the task from the current fields.
 *
 * @return The new task.
 * @throws std::invalid_argument If any value is not valid.
 */
std::unique_ptr<Task> TaskDialog::buildTaskFromFields() const {
    const std::string title = this->titleEdit->text().trimmed().toStdString();
    const std::string description = this->descriptionEdit->toPlainText().trimmed().toStdString();
    const TaskStatus status = statusFromInt(this->statusCombo->currentData().toInt());
    const QString type = this->typeCombo->currentData().toString();

    if (title.empty()) {
        throw std::invalid_argument("The title cannot be empty.");
    }

    if (type == typePriority) {
        const TaskPriority priority = priorityFromInt(this->priorityCombo->currentData().toInt());
        return std::make_unique<PriorityTask>(title, description, status, priority);
    }

    if (type == typeDate) {
        const QDate date = this->dateEdit->date();
        // The TaskWithDate constructor throws std::invalid_argument for an invalid date.
        return std::make_unique<TaskWithDate>(title, description, status, date.day(), date.month(), date.year());
    }

    return std::make_unique<Task>(title, description, status);
}

/**
 * @brief Validates the data; the dialog only closes when everything is valid.
 */
void TaskDialog::accept() {
    try {
        this->createdTask = this->buildTaskFromFields();
    } catch (const std::invalid_argument& error) {
        QMessageBox::warning(this, tr("Invalid data"), QString::fromStdString(error.what()));
        this->titleEdit->setFocus();
        return;  // Stay open.
    }

    QDialog::accept();
}

/**
 * @brief Gives the task created when the user pressed OK.
 *
 * @return The new task, or nullptr.
 */
std::unique_ptr<Task> TaskDialog::takeTask() {
    return std::move(this->createdTask);
}

/**
 * @brief Copies the validated data into an existing task (edit mode).
 *
 * @param task Task to update.
 */
void TaskDialog::applyTo(Task& task) const {
    if (!this->createdTask) {
        return;
    }

    task.setTitle(this->createdTask->getTitle());
    task.setDescription(this->createdTask->getDescription());
    task.setStatus(this->createdTask->getStatus());

    auto* target = dynamic_cast<PriorityTask*>(&task);
    const auto* source = dynamic_cast<const PriorityTask*>(this->createdTask.get());
    if (target != nullptr && source != nullptr) {
        target->setPriority(source->getPriority());
    }

    auto* dateTarget = dynamic_cast<TaskWithDate*>(&task);
    const auto* dateSource = dynamic_cast<const TaskWithDate*>(this->createdTask.get());
    if (dateTarget != nullptr && dateSource != nullptr) {
        dateTarget->setDate(dateSource->getDay(), dateSource->getMonth(), dateSource->getYear());
    }
}
