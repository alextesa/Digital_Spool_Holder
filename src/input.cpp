#include "input.h"
#include "ui.h"
#include "calibration.h"

#define BTN_UP     25
#define BTN_DOWN   26
#define BTN_SELECT 27

void inputInit() {
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_SELECT, INPUT_PULLUP);
}

void handleInput() {
    static bool lastUp = HIGH, lastDown = HIGH, lastSel = HIGH;

    bool up = digitalRead(BTN_UP);
    bool down = digitalRead(BTN_DOWN);
    bool sel = digitalRead(BTN_SELECT);

    if (lastSel == HIGH && sel == LOW) {
        handleSelect();
        if (currentScreen == CALIBRAR)
            calNextStep();
    }

    if (lastUp == HIGH && up == LOW) handleUp();
    if (lastDown == HIGH && down == LOW) handleDown();

    lastUp = up;
    lastDown = down;
    lastSel = sel;
}
