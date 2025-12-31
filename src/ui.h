#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "scale.h"

// ================= PANTALLAS =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
enum Screen { SPLASH, PRINCIPAL, MENU };

// ================= MENÚ =================
enum MenuOption { MENU_PESO, MENU_CALIBRAR, MENU_OPCIONES, MENU_TARA };
#define MENU_COUNT 4

extern Screen currentScreen;
extern MenuOption currentMenu;
extern const char* menuText[MENU_COUNT];
extern unsigned long lastInteraction;

// ================= FUNCIONES =================
void uiInit();
void uiLoop();

// Renderizado
void renderSplash();
void renderPrincipal();
void renderMenu();

// Navegación de menú
void menuUp();
void menuDown();
MenuOption menuSelect();
