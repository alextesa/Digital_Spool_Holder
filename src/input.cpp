#include <Arduino.h>
#include "input.h"

// ================= INICIALIZACIÓN PINES =================
void inputInit() {
    pinMode(PIN_SELECT, INPUT_PULLUP);
    pinMode(PIN_UP, INPUT_PULLUP);
    pinMode(PIN_DOWN, INPUT_PULLUP);
}

// ================= LECTURA BOTONES =================
InputButton readButton() {
    if (digitalRead(PIN_SELECT) == LOW) {
        Serial.println("[INPUT] SELECT presionado");
        return BTN_SELECT;
    }
    if (digitalRead(PIN_UP) == LOW) {
        Serial.println("[INPUT] UP presionado");
        return BTN_UP;
    }
    if (digitalRead(PIN_DOWN) == LOW) {
        Serial.println("[INPUT] DOWN presionado");
        return BTN_DOWN;
    }

    return BTN_NONE;
}
