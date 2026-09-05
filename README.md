# 📝 C++ To-Do List

Console application developed in **C++** to manage a task list using object-oriented programming.

This project will be developed throughout the semester in **3 phases**, progressively incorporating concepts such as OOP, inheritance, polymorphism, data persistence, file handling, databases, and exception handling.

---

## 🚀 Overview

The project consists of building a **To-Do List application** that allows users to manage their activities through a console interface.

### Project Phases

| Phase       | Content                                    | Status         |
| ----------- | ------------------------------------------ | -------------- |
| **Phase 1** | OOP fundamentals and in-memory CRUD        | 🟡 In progress |
| **Phase 2** | Inheritance, polymorphism, and overloading | ⚪ Pending      |
| **Phase 3** | Database, file handling, and exceptions    | ⚪ Pending      |

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
=============================
          TO-DO LIST
=============================

1. Add task
2. List tasks
3. Change status
4. Delete task
5. Exit

Select an option:
```

The user will be able to select an option and manage their tasks.

---

# 📊 Task Statuses

Tasks can have one of the following statuses:

```text
PENDING
IN PROGRESS
COMPLETED
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
git commit -m "feat: create Task class"
git push
```

Small and descriptive commits are recommended.

### Commit Examples

```text
feat: create Task class
feat: implement TaskList
feat: add task creation functionality
feat: implement task listing
feat: implement status change
feat: implement task deletion
fix: validate menu option
fix: validate task ID
docs: update README
docs: add UML diagram
```

---

# 🌿 Branches

To avoid working directly on `main`, branches are recommended:

```text
main
│
├── feature/task
├── feature/task-list
├── feature/menu
├── feature/validation
└── docs/uml
```

Once a feature is completed, it can be integrated through a Pull Request.

---

# 🗺️ Roadmap

## 🟡 Phase 1 — Fundamentals

* [ ] Create `Task` class.
* [ ] Create `TaskList` class.
* [ ] Implement task creation.
* [ ] Implement task listing.
* [ ] Implement status changes.
* [ ] Implement task deletion.
* [ ] Implement menu.
* [ ] Add input validation.
* [ ] Create UML diagram.
* [ ] Document Kanban board.
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
| Member 1 | Development             |
| Member 2 | Development             |
| Member 3 | Development             |
| Member 4 | Development             |

> Update this section with the actual names and responsibilities of the team members.

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
