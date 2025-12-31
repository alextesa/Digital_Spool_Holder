#include "input.h"
#include <Arduino.h>

// Variables internas de debounce y flanco
static bool lastSelect = HIGH;
static bool lastUp     = HIGH;
static bool lastDown   = HIGH;

static unsigned long lastSelectTime = 0;
static unsigned long lastUpTime     = 0;
static unsigned long lastDownTime   = 0;

const unsigned long DEBOUNCE_MS = 30; // ms

// Inicializa los pines de los botones
void inputInit() {
    pinMode(PIN_SELECT, INPUT_PULLUP);
    pinMode(PIN_UP, INPUT_PULLUP);
    pinMode(PIN_DOWN, INPUT_PULLUP);
}

// Devuelve el botón presionado una vez o BTN_NONE
Button readButton() {
    unsigned long now = millis();
    bool s = digitalRead(PIN_SELECT);
    bool u = digitalRead(PIN_UP);
    bool d = digitalRead(PIN_DOWN);

    // SELECT
    if (lastSelect == HIGH && s == LOW && (now - lastSelectTime) > DEBOUNCE_MS) {
        lastSelectTime = now;
        lastSelect = s;
        return BTN_SELECT;
    }
    lastSelect = s;

    // UP
    if (lastUp == HIGH && u == LOW && (now - lastUpTime) > DEBOUNCE_MS) {
        lastUpTime = now;
        lastUp = u;
        return BTN_UP;
    }
    lastUp = u;

    // DOWN
    if (lastDown == HIGH && d == LOW && (now - lastDownTime) > DEBOUNCE_MS) {
        lastDownTime = now;
        lastDown = d;
        return BTN_DOWN;
    }
    lastDown = d;

    return BTN_NONE;
}

// Solo para debug: imprime los botones presionados
void checkButtons() {
    Button b = readButton();
    switch (b) {
        case BTN_SELECT: Serial.println("Botón SELECT presionado"); break;
        case BTN_UP:     Serial.println("Botón UP presionado"); break;
        case BTN_DOWN:   Serial.println("Botón DOWN presionado"); break;
        case BTN_NONE:   break;
    }
}
