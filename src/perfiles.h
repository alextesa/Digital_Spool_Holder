#pragma once
#include <Arduino.h>
#include <vector>

struct Perfil {
    String nombre;
    int pesoCarrete;
};

// Vector que contiene todos los perfiles (en RAM)
extern std::vector<Perfil> perfiles;

// Funciones para manejar perfiles
Perfil crearPerfil(const String& nombre, int pesoCarrete);
void editarPerfil(int index, const String& nuevoNombre, int nuevoPeso);
void eliminarPerfil(int index);
Perfil* obtenerPerfil(int index);       // devuelve puntero para modificar
int contarPerfiles();
void listarPerfiles();
void cargarPerfil(int index);