// Small program to try TaskDialog without waiting for MainWindow.
// It opens the dialog, and if you press OK it opens it again in edit mode
// with the task you just created.
#include "TaskDialog.hpp"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    TaskDialog createDialog;
    if (createDialog.exec() != QDialog::Accepted) {
        return 0;
    }

    std::unique_ptr<Task> task = createDialog.takeTask();
    QMessageBox::information(nullptr, QStringLiteral("Created"),
        QString::fromStdString(task->getTitle() + " (" + task->getType() + ")\n" + task->toString()));

    TaskDialog editDialog(*task);
    if (editDialog.exec() == QDialog::Accepted) {
        editDialog.applyTo(*task);
        QMessageBox::information(nullptr, QStringLiteral("Edited"),
            QString::fromStdString(task->getTitle() + "\n" + task->toString()));
    }

    return 0;
}
