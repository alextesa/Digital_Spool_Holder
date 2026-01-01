#pragma once
#include <Arduino.h>

// Pines de los botones
#define PIN_SELECT 25
#define PIN_UP     26
#define PIN_DOWN   27

// Definición de botones
enum InputButton {
    BTN_NONE,
    BTN_UP,
    BTN_DOWN,
    BTN_SELECT
};

// Inicializa los pines de entrada
void inputInit();

// Lee los botones con debounce
InputButton readButton();

// Solo para debug: imprime los botones presionados
InputButton checkButtons();
