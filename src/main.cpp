#include <Arduino.h>
#include "ui.h"
#include "input.h"
#include "scale_ctrl.h"

void setup() {
    Serial.begin(115200);
    scaleInit();
    uiInit();
    inputInit();
}

void loop() {
    handleInput();
    uiLoop();
}
