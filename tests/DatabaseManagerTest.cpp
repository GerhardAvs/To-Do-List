#include "DatabaseManager.hpp"
#include "PriorityTask.hpp"
#include "TaskList.hpp"
#include "TaskWithDate.hpp"

#include <QCoreApplication>
#include <QFile>

#include <iostream>

namespace {

int failures = 0;

/**
 * @brief Prints OK or FAIL for one check.
 *
 * @param condition Result of the check.
 * @param name What was checked.
 */
void check(bool condition, const std::string& name) {
    std::cout << (condition ? "  OK    " : "  FAIL  ") << name << '\n';
    if (!condition) {
        ++failures;
    }
}

}  // namespace

/**
 * @brief Saves tasks of every type, closes the database, opens it again and
 *        checks that loadTasks() rebuilds them with the same type and status.
 *
 * @return 0 when every check passes, 1 otherwise.
 */
int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    const QString path = "test_tasks.db";
    QFile::remove(path);

    int normalId = -1;
    int urgentId = -1;
    int examId = -1;

    {
        DatabaseManager database(path, "first_run");
        check(database.connect() && database.createTable(), "connect() and createTable()");

        Task normal("Comprar pan", "En la tienda de la esquina");
        PriorityTask urgent("Entregar fase 3", "Subir el proyecto", TaskStatus::InProgress, TaskPriority::High);
        TaskWithDate exam("Examen de POO", "Repasar herencia", 26, 11, 2026);
        Task quotes("Tarea con 'comillas'", "x'); DROP TABLE tasks; --");

        std::cout << "saveTask()\n";
        check(database.saveTask(normal) && database.saveTask(urgent) &&
              database.saveTask(exam) && database.saveTask(quotes), "4 tasks saved");
        normalId = normal.getId();
        urgentId = urgent.getId();
        examId = exam.getId();
        check(normalId > 0 && urgentId != normalId && examId != urgentId, "each task got its own id");

        std::cout << "updateStatus()\n";
        normal.setStatus(TaskStatus::Completed);
        check(database.updateStatus(normal), "Task overload updates the row");
        check(database.updateStatus(examId, TaskStatus::InProgress), "update by id");
        check(!database.updateStatus(9999, TaskStatus::Pending), "unknown id returns false");

        std::cout << "deleteTask()\n";
        check(database.deleteTask(quotes.getId()), "delete existing task");
        check(!database.deleteTask(quotes.getId()), "deleting it again returns false");
    }   // the database closes here, like closing the app

    std::cout << "Reopen and loadTasks()\n";
    DatabaseManager reopened(path, "second_run");
    TaskList list;
    check(reopened.connect() && reopened.loadTasks(list), "loadTasks() after reopening");
    check(list.getTaskCount() == 3, "3 tasks come back (the deleted one does not)");

    if (list.getTaskCount() == 3) {
        const auto& tasks = list.getTasks();
        check(tasks[0]->getTypeName() == "Normal" && tasks[0]->getStatus() == TaskStatus::Completed,
              "normal task: type Normal, status Completed");

        const auto* urgent = dynamic_cast<const PriorityTask*>(tasks[1].get());
        check(urgent != nullptr && urgent->getPriority() == TaskPriority::High &&
              urgent->getStatus() == TaskStatus::InProgress,
              "priority task: type Priority, High, In progress");

        const auto* exam = dynamic_cast<const TaskWithDate*>(tasks[2].get());
        check(exam != nullptr && exam->getDate() == "2026-11-26" &&
              exam->getStatus() == TaskStatus::InProgress,
              "dated task: type With due date, 2026-11-26, In progress");

        check(tasks[0]->getId() == normalId && tasks[1]->getId() == urgentId && tasks[2]->getId() == examId,
              "loaded tasks keep their ids");
        check(reopened.deleteTask(tasks[1]->getId()), "a loaded task can be deleted with its id");
    }

    reopened.disconnect();
    QFile::remove(path);
    std::cout << (failures == 0 ? "\nAll checks passed\n" : "\nSome checks failed\n");
    return failures == 0 ? 0 : 1;
}
