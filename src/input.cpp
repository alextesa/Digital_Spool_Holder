#include <Arduino.h>
#include "input.h"
#include "ui.h"  // Asume que aquí tienes currentScreen, currentMenu, currentPerfilOption, handleMenuSelect(), perfilSelect(), menuNavigate(), renderMenuGenerico(), etc.

// ================= VARIABLES DE DEBOUNCE =================
static unsigned long lastSelectTime = 0;
static unsigned long lastUpTime     = 0;
static unsigned long lastDownTime   = 0;

// ================= INICIALIZACIÓN PINES =================
void inputInit() {
    pinMode(PIN_SELECT, INPUT_PULLUP);
    pinMode(PIN_UP, INPUT_PULLUP);
    pinMode(PIN_DOWN, INPUT_PULLUP);
}

InputButton readButton() {
    unsigned long now = millis();

    bool s = digitalRead(PIN_SELECT);
    bool u = digitalRead(PIN_UP);
    bool d = digitalRead(PIN_DOWN);

    static bool lastS = HIGH;
    static bool lastU = HIGH;
    static bool lastD = HIGH;

    const unsigned long DEBOUNCE_MS = 50; // tiempo mínimo entre pulsos
    static unsigned long lastTime = 0;

    // SELECT
    if (s == LOW && lastS == HIGH && (now - lastTime) > DEBOUNCE_MS) {
        lastS = s;
        lastTime = now;
        Serial.println("[INPUT] SELECT presionado");
        return BTN_SELECT;
    }

    // UP
    if (u == LOW && lastU == HIGH && (now - lastTime) > DEBOUNCE_MS) {
        lastU = u;
        lastTime = now;
        Serial.println("[INPUT] UP presionado");
        return BTN_UP;
    }

    // DOWN
    if (d == LOW && lastD == HIGH && (now - lastTime) > DEBOUNCE_MS) {
        lastD = d;
        lastTime = now;
        Serial.println("[INPUT] DOWN presionado");
        return BTN_DOWN;
    }

    // Actualizar estado de botones
    lastS = s;
    lastU = u;
    lastD = d;

    return BTN_NONE;
}
