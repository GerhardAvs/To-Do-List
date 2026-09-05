# 📝 To-Do List en C++

Aplicación de consola desarrollada en **C++** para administrar una lista de tareas mediante programación orientada a objetos.

Este proyecto será desarrollado durante el semestre en **3 fases**, incorporando progresivamente conceptos de POO, herencia, polimorfismo, persistencia de datos, archivos, bases de datos y manejo de excepciones.

---

## 🚀 Visión general

El proyecto consiste en construir una aplicación de **lista de tareas (To-Do List)** capaz de permitir al usuario administrar sus actividades desde una interfaz de consola.

### Fases del proyecto

| Fase       | Contenido                             | Estado           |
| ---------- | ------------------------------------- | ---------------- |
| **Fase 1** | Fundamentos de POO y CRUD en memoria  | 🟡 En desarrollo |
| **Fase 2** | Herencia, polimorfismo y sobrecarga   | ⚪ Pendiente      |
| **Fase 3** | Base de datos, archivos y excepciones | ⚪ Pendiente      |

---

# 📌 Fase 1 — Fundamentos

En esta primera fase se desarrolla la versión básica de la aplicación.

El programa permitirá administrar tareas almacenadas **en memoria**, utilizando clases y objetos.

## Funcionalidades

* ➕ Agregar una tarea.
* 📋 Listar todas las tareas.
* 🔄 Cambiar el estado de una tarea.
* 🗑️ Eliminar una tarea.
* ✅ Validar entradas del usuario.
* 💻 Interactuar mediante un menú de consola.

---

# 🏗️ Diseño del proyecto

La Fase 1 utiliza principalmente dos clases:

### `Tarea`

Representa una tarea individual.

Sus principales atributos son:

* Descripción.
* Estado.
* Fecha de creación.

Los atributos serán privados para aplicar **encapsulamiento**.

### `ListaTareas`

Se encarga de administrar la colección de objetos `Tarea`.

Entre sus responsabilidades se encuentran:

* Agregar tareas.
* Mostrar tareas.
* Modificar tareas.
* Eliminar tareas.
* Buscar tareas cuando sea necesario.

---

# 📂 Estructura del proyecto

```text
todo-list-cpp/
│
├── README.md
├── .gitignore
│
├── docs/
│   ├── kanban.md
│   └── diagramas/
│       ├── fase-1/
│       ├── fase-2/
│       └── fase-3/
│
├── src/
│   ├── main.cpp
│   ├── Tarea.h
│   ├── Tarea.cpp
│   ├── ListaTareas.h
│   ├── ListaTareas.cpp
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

### Descripción de carpetas

| Carpeta/archivo   | Descripción                                                        |
| ----------------- | ------------------------------------------------------------------ |
| `src/`            | Código fuente del proyecto.                                        |
| `include/`        | Headers compartidos si el proyecto crece.                          |
| `tests/`          | Pruebas y casos de prueba.                                         |
| `docs/`           | Documentación del proyecto.                                        |
| `docs/kanban.md`  | Información y bitácora del tablero Kanban.                         |
| `docs/diagramas/` | Diagramas UML de las diferentes fases.                             |
| `build/`          | Archivos generados durante la compilación.                         |
| `db/`             | Archivos y scripts relacionados con la base de datos de la Fase 3. |

---

# 🛠️ Tecnologías

* **C++**
* **Git**
* **GitHub**
* **GitHub Projects / Kanban**
* **UML**

Durante las siguientes fases se incorporarán nuevas tecnologías relacionadas con persistencia y bases de datos.

---

# ▶️ Compilación y ejecución

Desde la raíz del proyecto:

```bash
g++ src/*.cpp -o build/todo-list
```

Después:

```bash
./build/todo-list
```

> En Windows, el ejecutable puede generarse como `todo-list.exe`.

---

# 🎮 Uso

Al iniciar el programa se mostrará un menú similar a:

```text
=============================
       TO-DO LIST
=============================

1. Agregar tarea
2. Listar tareas
3. Cambiar estado
4. Eliminar tarea
5. Salir

Selecciona una opción:
```

El usuario podrá seleccionar una opción y administrar sus tareas.

---

# 📊 Estados de una tarea

Las tareas podrán encontrarse en alguno de los siguientes estados:

```text
PENDIENTE
EN PROGRESO
COMPLETADA
```

---

# 🧪 Validación

El programa deberá evitar que entradas inválidas provoquen errores o terminen inesperadamente la aplicación.

Se contemplan casos como:

* Opciones de menú inexistentes.
* IDs de tareas que no existen.
* Entradas vacías.
* Datos con formato incorrecto.
* Intentos de modificar o eliminar tareas inexistentes.

---

# 📐 Programación Orientada a Objetos

El proyecto busca aplicar correctamente los principios fundamentales de la **Programación Orientada a Objetos**.

En la Fase 1 se trabajará principalmente con:

* Clases.
* Objetos.
* Encapsulamiento.
* Constructores.
* Métodos.
* Getters y setters.
* Composición/asociación entre clases.

Las fases posteriores incorporarán:

* Herencia.
* Polimorfismo.
* Sobrecarga.
* Manejo de excepciones.

---

# 📋 Organización del equipo

El desarrollo se organizará utilizando un tablero **Kanban**.

### Columnas

```text
Por hacer → En proceso → Terminado
```

Las tareas se dividirán entre los integrantes del equipo y se actualizarán conforme avance el proyecto.

La documentación del tablero y las revisiones semanales se encuentra en:

```text
docs/kanban.md
```

---

# 🔄 Flujo de trabajo con Git

Cada integrante deberá trabajar mediante Git y realizar commits conforme avance el proyecto.

### Ejemplo

```bash
git add .
git commit -m "feat: crear clase Tarea"
git push
```

Se recomienda realizar commits pequeños y descriptivos.

### Ejemplos de commits

```text
feat: crear clase Tarea
feat: implementar ListaTareas
feat: agregar funcionalidad para crear tareas
feat: implementar listado de tareas
feat: implementar cambio de estado
feat: implementar eliminación de tareas
fix: validar opción del menú
fix: validar ID de tarea
docs: actualizar README
docs: agregar diagrama UML
```

---

# 🌿 Ramas

Para evitar trabajar directamente sobre `main`, se recomienda utilizar ramas:

```text
main
│
├── feature/tarea
├── feature/lista-tareas
├── feature/menu
├── feature/validaciones
└── docs/uml
```

Una vez terminada una funcionalidad, se puede integrar mediante un Pull Request.

---

# 🗺️ Roadmap

## 🟡 Fase 1 — Fundamentos

* [ ] Crear clase `Tarea`.
* [ ] Crear clase `ListaTareas`.
* [ ] Implementar agregar tarea.
* [ ] Implementar listar tareas.
* [ ] Implementar cambio de estado.
* [ ] Implementar eliminar tarea.
* [ ] Implementar menú.
* [ ] Agregar validación de entradas.
* [ ] Crear diagrama UML.
* [ ] Documentar Kanban.
* [ ] Realizar pruebas.

## ⚪ Fase 2 — Herencia y polimorfismo

* [ ] Crear jerarquía de tipos de tarea.
* [ ] Implementar herencia.
* [ ] Implementar polimorfismo.
* [ ] Implementar sobrecarga.
* [ ] Actualizar el diagrama UML.
* [ ] Actualizar documentación.

## ⚪ Fase 3 — Persistencia

* [ ] Implementar persistencia.
* [ ] Integrar base de datos.
* [ ] Implementar manejo de archivos.
* [ ] Implementar excepciones.
* [ ] Actualizar CRUD.
* [ ] Realizar pruebas finales.
* [ ] Actualizar documentación.

---

# 🧪 Pruebas

Las pruebas deberán verificar principalmente:

| Prueba               | Resultado esperado                     |
| -------------------- | -------------------------------------- |
| Agregar tarea válida | La tarea se agrega correctamente       |
| Listar tareas        | Se muestran las tareas existentes      |
| Cambiar estado       | El estado se actualiza                 |
| Eliminar tarea       | La tarea desaparece de la lista        |
| ID inexistente       | Se muestra un mensaje de error         |
| Opción inválida      | El programa solicita una opción válida |
| Descripción vacía    | Se rechaza la entrada                  |

---

# 👥 Equipo

| Integrante   | Rol / responsabilidades |
| ------------ | ----------------------- |
| Integrante 1 | Desarrollo              |
| Integrante 2 | Desarrollo              |
| Integrante 3 | Desarrollo              |
| Integrante 4 | Desarrollo              |

> Actualizar esta sección con los nombres y responsabilidades reales del equipo.

---

# 📚 Documentación

La documentación adicional se encuentra en:

```text
docs/
```

Incluye:

* Diagramas UML.
* Organización Kanban.
* Revisiones semanales.
* Documentación técnica.

---

# 📄 Licencia

Este proyecto fue desarrollado con fines **académicos**.
