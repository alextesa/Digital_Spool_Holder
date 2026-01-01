#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>

// ===== ENUM BOTONES =====
enum InputButton {
    BTN_NONE = 0,
    BTN_UP,
    BTN_DOWN,
    BTN_SELECT
};

// ===== PINES =====
#define PIN_SELECT 25
#define PIN_UP     26
#define PIN_DOWN   27

// ===== FUNCIONES =====
void inputInit();
InputButton readButton();

#endif
