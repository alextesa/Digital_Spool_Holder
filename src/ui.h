#pragma once

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "input.h"
#include "scale.h"

// ================= PANTALLA =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// ================= MENÚ PRINCIPAL =================
enum MenuOption {
    MENU_PESO,
    MENU_CALIBRAR,
    MENU_PERFILES,
    MENU_TARA,
    MENU_COUNT
};

extern MenuOption currentMenu;
extern const char* menuText[MENU_COUNT];

// ================= ESTADOS DE UI =================
enum Screen {
    SPLASH,
    PRINCIPAL,
    MENU,
    SUBMENU_PERFILES,
    PERFIL_CREAR
};

extern Screen currentScreen;

// ================= CICLO UI =================
void uiInit();
void uiLoop();

// ================= RENDER GENÉRICO =================
void renderSplash();
void renderPrincipal();
void renderMenuGenerico(
    const char* titulo,
    const char** opciones,
    int count,
    int selected
);

// ================= NAVEGACIÓN GENÉRICA =================
void menuNavigate(int &index, int count, InputButton btn);

// ================= ACCIONES DEL MENÚ =================
void handleMenuSelect(MenuOption m);
void mostrarPeso();
void ejecutarTara();
void calibrar();
void abrirSubMenuPerfiles();

// ================= PERFILES / CREACIÓN =================
void perfilSelect();
void crearPerfilInteractivo(InputButton b);

void iniciarCreacionPerfil(); // prototipo