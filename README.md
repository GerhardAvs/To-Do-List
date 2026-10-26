# 📝 C++ To-Do List

Console application developed in **C++** to manage a task list using object-oriented programming.

This project is developed throughout the semester in **3 phases**, progressively incorporating concepts such as OOP, inheritance, polymorphism, data persistence, file handling, databases, and exception handling.

---

## 🚀 Overview

The project consists of building a **To-Do List application** that allows users to manage their activities through a console interface.

### Project Phases

| Phase       | Content                                    | Status         | Limit date (2026) | Score |
| ----------- | ------------------------------------------ | -------------- | ----------------- | ----- |
| **Phase 1** | OOP fundamentals and in-memory CRUD        | 🟢 Done        | Sep 18th          | 94%   |
| **Phase 2** | Inheritance, polymorphism, and overloading | 🟢 Done        | Oct 22nd          | —     |
| **Phase 3** | Database, file handling, and exceptions    | ⚪ Pending     | Nov 26th          | —     |

---

# 📌 Phase 1 — Fundamentals

The first version of the application manages tasks stored **in memory**, using classes and objects.

## Features

* ➕ Add a task.
* 📋 List all tasks.
* 🔄 Update a task (title, description, and status).
* 🗑️ Delete a task.
* ✅ Validate user input.
* 💻 Interact through a console menu.

---

# 📌 Phase 2 — Inheritance and Polymorphism

In the second phase, the application supports **different types of tasks** that share a common base class.

## Features

* 🏷️ Choose the task type when creating it: **Normal**, **With priority**, or **With due date**.
* ⚡ Priority tasks have a level: **Low**, **Medium**, or **High**.
* 📅 Tasks with a due date store a validated date (`YYYY-MM-DD`).
* ✏️ When updating a task, the program asks for the extra fields that belong to its type.
* 🖨️ Each task type prints its own details through polymorphism.

---

# 🏗️ Project Design

### Class Hierarchy

```text
            Task
             ▲
     ┌───────┴────────┐
PriorityTask     TaskWithDate
```

### `Task` (base class)

Represents an individual task.

Its main attributes are private in order to apply **encapsulation**:

* Title.
* Description.
* Status.
* Creation date (generated automatically, format `YYYY-MM-DD HH:MM`).

It declares the virtual methods `getTypeName()` and `printDetails()`, which the derived classes override, and a virtual destructor for correct polymorphic cleanup.

### `PriorityTask` (derived from `Task`)

Adds a **priority level** (`Low`, `Medium`, `High`).

The priority can be set with the enum value or with text (`"low"`, `"medium"`, `"high"`, or in Spanish `"baja"`, `"media"`, `"alta"`). Invalid text throws `std::invalid_argument` and leaves the priority unchanged.

### `TaskWithDate` (derived from `Task`)

Adds a **target due date** (day, month, and year). The date is validated, including the number of days in each month and leap years. Accepted years go from **2024 to 2100**.

### `TaskList`

Manages the collection of tasks using `std::vector<std::unique_ptr<Task>>`, so it can store any task type in the same list.

Its responsibilities include:

* Adding tasks (one `addTask()` overload for each task type).
* Updating title, description, status, priority, and date.
* Deleting tasks.
* Checking the type of a stored task.

### `Menu`

Console interface of the application. It handles every prompt and every print. Each option is registered with a label and the action it runs.

### `InputValidator`

Helper class that reads console input and never returns invalid data (numbers out of range, empty text, letters instead of numbers, etc.). If the input is closed (`Ctrl+D` / `Ctrl+Z`), it throws `InputClosedError` so the program exits cleanly.

---

# 📂 Project Structure

```text
To-Do-List/
│
├── README.md
├── LICENSE
├── .gitignore
│
├── docs/
│   ├── documentation/
│   │   └── Bitacora-POO-To-Do-List-Final.pdf
│   └── rol-structure/
│       ├── Bitacora-POO-To-Do-List-Actualizada.pdf
│       ├── Trello.png
│       └── kanban.md
│
├── include/
│   ├── InputValidator.hpp
│   ├── Menu.hpp
│   ├── PriorityTask.hpp
│   ├── Task.hpp
│   ├── TaskList.hpp
│   └── TaskWithDate.hpp
│
├── src/
│   ├── InputValidator.cpp
│   ├── Menu.cpp
│   ├── PriorityTask.cpp
│   ├── Task.cpp
│   ├── TaskList.cpp
│   ├── TaskWithDate.cpp
│   └── main.cpp
│
└── tests/
    └── PriorityTaskTest.cpp
```

### Folder Description

| Folder/File           | Description                                          |
| --------------------- | ---------------------------------------------------- |
| `include/`            | Header files (`.hpp`) with class declarations.       |
| `src/`                | Source files (`.cpp`) with the implementations.      |
| `tests/`              | Test programs.                                       |
| `docs/documentation/` | Final project log (bitácora).                        |
| `docs/rol-structure/` | Team organization, Kanban log, and Trello board.     |
| `build/`              | Compiled files (created locally, ignored by Git).    |

---

# 🛠️ Technologies

* **C++17**
* **g++**
* **Git**
* **GitHub**
* **Trello (Kanban)**

New technologies related to persistence and databases will be introduced in Phase 3.

---

# ▶️ Compilation and Execution

From the project root, create the `build` folder (it is ignored by Git, so it does not exist after cloning):

```bash
mkdir -p build
```

Compile the program:

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o build/todo-list
```

Run it:

```bash
./build/todo-list
```

> On Windows, use `mkdir build` and generate `build/todo-list.exe`. The menu uses box-drawing characters, so a terminal with UTF-8 support is recommended.

---

# 🎮 Usage

When the program starts, the following menu is displayed:

```text
╔══════════════════════════════════════════════╗
║         C++ To Do List Manager               ║
╚══════════════════════════════════════════════╝

  [1] Create a task
  [2] Read task/s
  [3] Update task
  [4] Delete a task

  [5] Exit
────────────────────────────────────────────────
Select an option: 
```

When creating a task, the program first asks for its type:

```text
  [1] Normal
  [2] With priority
  [3] With due date
Select task type: 
```

Then it asks for the title, description, and status. Depending on the type, it also asks for the priority level or the due date.

Example of the task list:

```text
--- TASK LIST (1) ---
  [1] Buy groceries (Priority)
      Description: Milk and bread
      Status: Pending | Created: 2026-10-25 22:28 | Priority: High
```

---

# 📊 Task Values

### Status

```text
PENDING     = 1
IN PROGRESS = 2
COMPLETED   = 3
```

### Priority (only for priority tasks)

```text
LOW    = 1
MEDIUM = 2
HIGH   = 3
```

### Due date (only for tasks with due date)

```text
Format: YYYY-MM-DD
Years:  2024 - 2100
```

---

# 🧪 Validation

The program prevents invalid input from causing errors or unexpectedly terminating the application.

Handled cases include:

* Non-existent menu options.
* Task numbers that do not exist.
* Empty title or description.
* Letters or symbols where a number is expected.
* Dates that do not exist (for example, February 30th).
* Priority text that is not recognized.
* Closed input stream (`Ctrl+D` / `Ctrl+Z`).

---

# 📐 Object-Oriented Programming

The project applies the fundamental principles of **Object-Oriented Programming**.

### Phase 1

* Classes and objects.
* Encapsulation.
* Constructors.
* Methods, getters, and setters.
* Composition between classes (`TaskList` contains `Task` objects).

### Phase 2

* **Inheritance:** `PriorityTask` and `TaskWithDate` derive from `Task`.
* **Polymorphism:** `getTypeName()` and `printDetails()` are virtual and overridden; tasks are stored as `std::unique_ptr<Task>`.
* **Overloading:**
  * Constructors of `Task`, `PriorityTask`, and `TaskWithDate`.
  * `TaskList::addTask()` (one version per task type).
  * `PriorityTask::setPriority()` (enum or text).
  * `operator<<` to print any task.

### Phase 3 (planned)

* Data persistence.
* File handling.
* Database.
* Exception handling.

---

# 📋 Team Organization

Development is organized using a **Kanban** board in **Trello**.

### Columns

```text
To Do → In Progress → Done
```

Tasks are distributed among team members and updated as the project progresses.

The board documentation and weekly reviews can be found at:

```text
docs/rol-structure/kanban.md
docs/rol-structure/Trello.png
```

---

# 🔄 Git Workflow

Each team member works on their own branch and makes commits as the project progresses.

### Example

```bash
git add .
git commit -m "feature/task: add TaskWithDate class"
git push
```

Small and descriptive commits are recommended.

### Commit Examples

```text
feature/task: create Task class
feature/task: implement TaskList
feature/priority: add PriorityTask class
feature/date: add TaskWithDate class
feature/menu: ask for task type
feature/menu: validate task number
test: add PriorityTask tests
docs: update README
```

---

# 🌿 Branches

Nobody works directly on `main`. Features are developed in their own branch, merged into `dev`, and once `dev` is stable it is merged into `main` through a Pull Request.

```text
main
│
└── dev
    ├── feature/PriorityTask
    ├── feature/TaskWithDate
    └── feature/docs
```

---

# 🗺️ Roadmap

## 🟢 Phase 1 — Fundamentals

* [x] Create `Task` class.
* [x] Create `TaskList` class.
* [x] Implement task creation.
* [x] Implement task listing.
* [x] Implement task updates.
* [x] Implement task deletion.
* [x] Implement menu.
* [x] Add input validation.
* [ ] Create UML diagram.
* [x] Document Kanban board.

## 🟢 Phase 2 — Inheritance and Polymorphism

* [x] Create a task type hierarchy.
* [x] Implement inheritance (`PriorityTask`, `TaskWithDate`).
* [x] Implement polymorphism.
* [x] Implement overloading.
* [x] Move headers to `include/`.
* [x] Add `PriorityTask` tests.
* [ ] Update UML diagram.
* [x] Update documentation.

## ⚪ Phase 3 — Persistence

* [ ] Implement data persistence.
* [ ] Integrate a database.
* [ ] Implement file handling.
* [ ] Implement exception handling.
* [ ] Update CRUD functionality.
* [ ] Perform final tests.
* [ ] Update documentation.

---

# 🧪 Testing

### Running the tests

```bash
mkdir -p build
g++ -std=c++17 -Iinclude tests/PriorityTaskTest.cpp src/PriorityTask.cpp src/Task.cpp -o build/priority-test
./build/priority-test
```

Each check prints `[OK]` or `[FAIL]`. The program returns `0` when every check passes.

### What is tested

| Test                                   | Expected Result                                  |
| -------------------------------------- | ------------------------------------------------ |
| `PriorityTask` constructors            | The priority is stored (default is `Medium`)     |
| `setPriority()` with enum              | The priority is updated                          |
| `setPriority()` with text              | Accepts English/Spanish, ignores case and spaces |
| `setPriority()` with invalid text      | Throws an exception and keeps the old priority   |

### Manual tests

| Test                    | Expected Result                         |
| ----------------------- | --------------------------------------- |
| Add valid task          | The task is added successfully          |
| List tasks              | Existing tasks are displayed            |
| Update task             | The task data is updated                |
| Delete task             | The task is removed from the list       |
| Non-existent task       | The program asks for a valid number     |
| Invalid option          | The program requests a valid option     |
| Empty description       | The input is rejected                   |
| Invalid date            | Only valid days for that month are asked |

---

# 👥 Team

| Member   | Role / Responsibilities |
| -------- | ----------------------- |
| Gerardo  | Main developer          |
| Daniel   | feature/task            |
| Isacar   | implement code on dev   |
| Ruben    | Documentation           |

---

# 📚 Documentation

Additional documentation can be found in the `docs/` folder:

* `docs/documentation/Bitacora-POO-To-Do-List-Final.pdf` — final project log.
* `docs/rol-structure/Bitacora-POO-To-Do-List-Actualizada.pdf` — updated log with roles.
* `docs/rol-structure/kanban.md` — Kanban organization and weekly reviews.
* `docs/rol-structure/Trello.png` — screenshot of the Trello board.

---

# 📄 License

This project was developed for **academic purposes** and is distributed under the **MIT License**. See the `LICENSE` file for details.