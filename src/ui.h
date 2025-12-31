#ifndef UI_H
#define UI_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// ================= CONFIG =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

enum Screen {
    SPLASH,
    PRINCIPAL
};

// ================= FUNCIONES =================
void uiInit();
void uiLoop();
void renderSplash();
void renderPrincipal();

#endif
