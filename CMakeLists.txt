cmake_minimum_required(VERSION 3.16)
project(ToDoList LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Model classes (no Qt, no console): shared by every program.
add_library(todo_model STATIC
    src/Task.cpp
    src/PriorityTask.cpp
    src/TaskWithDate.cpp
    src/TaskList.cpp
    src/FileManager.cpp
)
target_include_directories(todo_model PUBLIC include)

# Phase 2 console program (still works without Qt).
add_executable(todo-console src/main.cpp src/Menu.cpp src/InputValidator.cpp)
target_link_libraries(todo-console PRIVATE todo_model)

add_executable(priority-test tests/PriorityTaskTest.cpp)
target_link_libraries(priority-test PRIVATE todo_model)

add_executable(file-test tests/FileManagerTest.cpp)
target_link_libraries(file-test PRIVATE todo_model)

# Phase 3: Qt parts.
find_package(Qt6 COMPONENTS Widgets Sql REQUIRED)

add_executable(task-dialog-demo
    tests/TaskDialogDemo.cpp
    src/TaskDialog.cpp
    include/TaskDialog.hpp   # listed so AUTOMOC finds Q_OBJECT
)
target_link_libraries(task-dialog-demo PRIVATE todo_model Qt6::Widgets)

# Main window of the Qt app (MainWindow + TaskDialog).
add_executable(todo-gui
    src/mainGui.cpp
    src/MainWindow.cpp
    include/MainWindow.hpp   # listed so AUTOMOC finds Q_OBJECT
    src/TaskDialog.cpp
    include/TaskDialog.hpp
)
target_link_libraries(todo-gui PRIVATE todo_model Qt6::Widgets)
