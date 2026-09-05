# To-Do-List
Aplicación de consola en C++ para administrar tareas, desarrollada en 3 fases (POO en memoria → herencia y polimorfismo → persistencia en base de datos), como proyecto del curso.

todo-list-cpp/
├── README.md
├── .gitignore
│
├── docs/
│   ├── kanban.md              # Enlace/capturas del tablero y bitácora de revisiones semanales
│   └── diagramas/              # Diagramas de clases (UML) por fase
│
├── src/
│   ├── main.cpp                 # Punto de entrada / menú de consola
│   ├── Tarea.h
│   ├── Tarea.cpp
│   ├── ListaTareas.h
│   ├── ListaTareas.cpp
│   └── ...                        # Nuevas clases que se agreguen en Fase 2 y 3
│
├── include/                     # (opcional) headers compartidos si el proyecto crece
│
├── tests/                        # (opcional) pruebas manuales o casos de prueba
│
├── build/                        # Archivos generados al compilar (ignorado por git)
│
└── db/                             # Fase 3: scripts o archivo de base de datos
