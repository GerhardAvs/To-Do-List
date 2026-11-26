#include "MainWindow.hpp"

#include <QApplication>

/**
 * @brief Entry point of the Qt version: opens the main window.
 *
 * @param argc Argument count.
 * @param argv Argument values.
 * @return Exit code returned by the Qt event loop.
 */
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
