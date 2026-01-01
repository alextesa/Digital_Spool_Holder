#include <Arduino.h>
#include "perfiles.h"
#include <vector>

// Vector global de perfiles en memoria RAM
std::vector<Perfil> perfiles;

// ================= INICIALIZACION =================
void inicializarPerfiles() {
    // Aquí puedes cargar perfiles desde EEPROM o archivo
    // Por ahora dejamos algunos de ejemplo
    perfiles.clear();
    perfiles.push_back({"PLA Blanco", 1000});
    perfiles.push_back({"ABS Negro", 1200});
}

// ================= ACCESO =================
std::vector<Perfil>& obtenerPerfiles() {
    return perfiles;
}

// ================= CARGAR =================
void cargarPerfil(int index) {
    if(index < 0 || index >= perfiles.size()) return;
    Perfil p = perfiles[index];
    Serial.print("[PERFIL] Cargando: ");
    Serial.print(p.nombre);
    Serial.print(" - ");
    Serial.print(p.pesoCarrete);
    Serial.println("g");
    // Aquí puedes guardar el perfil seleccionado en una variable global si quieres
}

// ================= CREAR =================
Perfil crearPerfil(const String& nombre, int pesoCarrete) {
    Perfil p = {nombre, pesoCarrete};
    perfiles.push_back(p);
    Serial.print("[PERFIL] Creado: "); 
    Serial.print(nombre);
    Serial.print(" - "); 
    Serial.print(pesoCarrete); 
    Serial.println("g");
    return p;
}

// ================= EDITAR =================
void editarPerfil(int index, const String& nombre, int pesoCarrete) {
    if(index < 0 || index >= perfiles.size()) return;
    perfiles[index].nombre = nombre;
    perfiles[index].pesoCarrete = pesoCarrete;
    Serial.print("[PERFIL] Editado: "); 
    Serial.print(nombre);
    Serial.print(" - "); 
    Serial.print(pesoCarrete); 
    Serial.println("g");
}

// ================= ELIMINAR =================
void eliminarPerfil(int index) {
    if(index < 0 || index >= perfiles.size()) return;
    Serial.print("[PERFIL] Eliminado: "); 
    Serial.println(perfiles[index].nombre);
    perfiles.erase(perfiles.begin() + index);
}

// ================= OBTENER =================
Perfil* obtenerPerfil(int index) {
    if(index < 0 || index >= perfiles.size()) return nullptr;
    return &perfiles[index];
}

// ================= CONTAR =================
int contarPerfiles() {
    return perfiles.size();
}

// ================= LISTAR =================
void listarPerfiles() {
    Serial.println("[PERFILES]");
    for(int i = 0; i < perfiles.size(); i++) {
        Serial.print(i);
        Serial.print(": ");
        Serial.print(perfiles[i].nombre);
        Serial.print(" - ");
        Serial.print(perfiles[i].pesoCarrete);
        Serial.println("g");
    }
}

