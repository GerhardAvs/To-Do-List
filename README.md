# 📝 C++ To-Do List

Console application developed in **C++** to manage a task list using object-oriented programming.

This project will be developed throughout the semester in **3 phases**, progressively incorporating concepts such as OOP, inheritance, polymorphism, data persistence, file handling, databases, and exception handling.

---

## 🚀 Overview

The project consists of building a **To-Do List application** that allows users to manage their activities through a console interface.

### Project Phases

| Phase       | Content                                    | Status          | Limit date (2026) | Score |
| ----------- | ------------------------------------------ | --------------- | ----------------- | ----- |  
| **Phase 1** | OOP fundamentals and in-memory CRUD        | 🟢 Done         |   Sep 18th       |  94%  |
| **Phase 2** | Inheritance, polymorphism, and overloading | 🟠 In progress  |   Oct 22nd       |   0%  |
| **Phase 3** | Database, file handling, and exceptions    | ⚪ Pending      |   Nov 26th       |   0%  |

---

# 📌 Phase 1 — Fundamentals

In this first phase, the basic version of the application will be developed.

The program will manage tasks stored **in memory**, using classes and objects.

## Features

* ➕ Add a task.
* 📋 List all tasks.
* 🔄 Change the status of a task.
* 🗑️ Delete a task.
* ✅ Validate user input.
* 💻 Interact through a console menu.

---

# 🏗️ Project Design

Phase 1 mainly uses two classes:

### `Task`

Represents an individual task.

Its main attributes are:

* Description.
* Status.
* Creation date.

The attributes will be private in order to apply **encapsulation**.

### `TaskList`

Responsible for managing the collection of `Task` objects.

Its responsibilities include:

* Adding tasks.
* Displaying tasks.
* Modifying tasks.
* Deleting tasks.
* Searching for tasks when necessary.

---

# 📂 Project Structure

```text
todo-list-cpp/
│
├── README.md
├── .gitignore
│
├── docs/
│   ├── kanban.md
│   └── diagrams/
│       ├── phase-1/
│       ├── phase-2/
│       └── phase-3/
│
├── src/
│   ├── main.cpp
│   ├── Task.h
│   ├── Task.cpp
│   ├── TaskList.h
│   ├── TaskList.cpp
│   └── ...
│
├── include/
│
├── tests/
│
├── build/
│
└── db/
```

### Folder Description

| Folder/File      | Description                                        |
| ---------------- | -------------------------------------------------- |
| `src/`           | Project source code.                               |
| `include/`       | Shared headers if the project grows.               |
| `tests/`         | Tests and test cases.                              |
| `docs/`          | Project documentation.                             |
| `docs/kanban.md` | Information and activity log for the Kanban board. |
| `docs/diagrams/` | UML diagrams for the different phases.             |
| `build/`         | Files generated during compilation.                |
| `db/`            | Database-related files and scripts for Phase 3.    |

---

# 🛠️ Technologies

* **C++**
* **Git**
* **GitHub**
* **GitHub Projects / Kanban**
* **UML**

New technologies related to persistence and databases will be introduced during the following phases.

---

# ▶️ Compilation and Execution

From the project root:

```bash
g++ src/*.cpp -o build/todo-list
```

Then:

```bash
./build/todo-list
```

> On Windows, the executable can be generated as `todo-list.exe`.

---

# 🎮 Usage

When the program starts, a menu similar to the following will be displayed:

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

The user will be able to select an option and manage their tasks.

---

# 📊 Task Statuses

Tasks can have one of the following statuses:

```text
PENDING = 1
IN PROGRESS = 2
COMPLETED = 3
```

---

# 🧪 Validation

The program must prevent invalid input from causing errors or unexpectedly terminating the application.

Cases to be considered include:

* Non-existent menu options.
* Task IDs that do not exist.
* Empty input.
* Incorrectly formatted data.
* Attempts to modify or delete non-existent tasks.

---

# 📐 Object-Oriented Programming

The project aims to correctly apply the fundamental principles of **Object-Oriented Programming**.

Phase 1 will mainly focus on:

* Classes.
* Objects.
* Encapsulation.
* Constructors.
* Methods.
* Getters and setters.
* Composition/association between classes.

Later phases will introduce:

* Inheritance.
* Polymorphism.
* Overloading.
* Exception handling.

---

# 📋 Team Organization

Development will be organized using a **Kanban** board.

### Columns

```text
To Do → In Progress → Done
```

Tasks will be distributed among team members and updated as the project progresses.

The board documentation and weekly reviews can be found at:

```text
docs/kanban.md
```

---

# 🔄 Git Workflow

Each team member should use Git and make commits as the project progresses.

### Example

```bash
git add .
git commit -m "dev: last updates"
git push
```

Small and descriptive commits are recommended.

### Commit Examples

```text
feature/task: create Task class
feature/task: implement TaskList
feature/task: add task creation functionality
feature/task: implement task listing
feature/task: implement status change
feature/task: implement task deletion
feature/menu: validate menu option
feature/menu: validate task ID
docs: add kanban
```

---

# 🌿 Branches

To avoid working directly on `main`, branches are recommended:

```text
main
│
├── feature/task
├── feature/menu
├── dev
└── docs
```

Once a feature is completed, it can be integrated through a Pull Request.

---

# 🗺️ Roadmap

## 🟡 Phase 1 — Fundamentals

* [x] Create `Task` class.
* [x] Create `TaskList` class.
* [x] Implement task creation.
* [x] Implement task listing.
* [x] Implement status changes.
* [x] Implement task deletion.
* [x] Implement menu.
* [x] Add input validation.
* [ ] Create UML diagram.
* [x] Document Kanban board.
* [ ] Perform tests.

## ⚪ Phase 2 — Inheritance and Polymorphism

* [ ] Create a task type hierarchy.
* [ ] Implement inheritance.
* [ ] Implement polymorphism.
* [ ] Implement overloading.
* [ ] Update UML diagram.
* [ ] Update documentation.

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

Tests should mainly verify the following:

| Test              | Expected Result                     |
| ----------------- | ----------------------------------- |
| Add valid task    | The task is added successfully      |
| List tasks        | Existing tasks are displayed        |
| Change status     | The task status is updated          |
| Delete task       | The task is removed from the list   |
| Non-existent ID   | An error message is displayed       |
| Invalid option    | The program requests a valid option |
| Empty description | The input is rejected               |

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

Additional documentation can be found in:

```text
docs/
```

It includes:

* UML diagrams.
* Kanban organization.
* Weekly reviews.
* Technical documentation.

---

# 📄 License

This project was developed for **academic purposes**.
