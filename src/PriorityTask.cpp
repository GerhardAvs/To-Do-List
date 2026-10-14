#include <iostream>
#include <stdexcept>
#include "PriorityTask.hpp"
 
static int failures = 0;
static void check(bool ok, const char* name) {
    std::cout << (ok ? "[OK]   " : "[FAIL] ") << name << "\n";
    if (!ok) ++failures;
}
 
int main() {
    PriorityTask a("A", "completa", TaskStatus::InProgress, TaskPriority::High);
    check(a.getPriority() == TaskPriority::High, "constructor de 4 parametros");
 
    PriorityTask b("B", "sin status", TaskPriority::Low);
    check(b.getPriority() == TaskPriority::Low, "constructor (titulo, descripcion, prioridad)");
 
    PriorityTask c("C", "minima");
    check(c.getPriority() == TaskPriority::Medium, "constructor (titulo, descripcion) -> Medium");
 
    c.setPriority(TaskPriority::High);
    check(c.getPriority() == TaskPriority::High, "setPriority(TaskPriority)");
 
    c.setPriority("low");
    check(c.getPriority() == TaskPriority::Low, "setPriority(\"low\")");
    c.setPriority("  ALTA ");
    check(c.getPriority() == TaskPriority::High, "setPriority(\"  ALTA \") ignora mayusculas y espacios");
    c.setPriority(std::string("media"));
    check(c.getPriority() == TaskPriority::Medium, "setPriority(std::string)");
 
    bool threw = false;
    try { c.setPriority("urgentisima"); } catch (const std::invalid_argument&) { threw = true; }
    check(threw && c.getPriority() == TaskPriority::Medium, "texto invalido lanza excepcion y no cambia la prioridad");
 
    a.printDetails(std::cout); std::cout << "\n";
    return failures;
}
 