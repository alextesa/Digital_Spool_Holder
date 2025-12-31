#include "ui.h"
#include "scale_ctrl.h"
#include "calibration.h"
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define MENU_TIMEOUT 15000

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Screen currentScreen = PRINCIPAL;
unsigned long lastInteraction = 0;
int menuIndex = 0;
const int menuItems = 3;

void uiInit() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();
}

void uiLoop() {
    switch (currentScreen) {
        case PRINCIPAL: renderPeso(); break;
        case MENU: renderMenu(); break;
        case CALIBRAR: renderCalibrar(); break;
        case PERFILES: renderPerfiles(); break;
    }

    if (millis() - lastInteraction > MENU_TIMEOUT && currentScreen != PRINCIPAL)
        currentScreen = PRINCIPAL;
}

void renderPeso() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    String s = String(leerPesoFiltrado(), 1) + " g";
    display.setCursor(10, 25);
    display.print(s);
    display.display();
}

void renderMenu() {
    display.clearDisplay();
    display.setTextSize(1);
    for (int i = 0; i < menuItems; i++) {
        if (i == menuIndex)
            display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        else
            display.setTextColor(SSD1306_WHITE);

        display.setCursor(0, i * 10);
        if (i == 0) display.print("Calibrar");
        if (i == 1) display.print("Perfiles");
        if (i == 2) display.print("Opciones");
    }
    display.display();
}

void renderCalibrar() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    if (getCalState() == CAL_TARA) display.println("Paso 1: TARA");
    if (getCalState() == CAL_PESO_REF) display.println("Paso 2: PESO");
    if (getCalState() == CAL_AJUSTE) display.println("Paso 3: AJUSTE");
    if (getCalState() == CAL_GUARDAR) display.println("Paso 4: GUARDAR");
    if (getCalState() == CAL_FINALIZADO) display.println("LISTO");

    display.display();
}

void renderPerfiles() {
    display.clearDisplay();
    display.println("Perfiles (WIP)");
    display.display();
}

void handleSelect() {
    lastInteraction = millis();
    if (currentScreen == PRINCIPAL) currentScreen = MENU;
    else if (currentScreen == MENU && menuIndex == 0) {
        currentScreen = CALIBRAR;
        calInit(236.0);
    }
    else if (currentScreen == CALIBRAR && getCalState() == CAL_FINALIZADO)
        currentScreen = PRINCIPAL;
}

void handleUp() {
    lastInteraction = millis();
    if (currentScreen == MENU)
        menuIndex = (menuIndex - 1 + menuItems) % menuItems;
}

void handleDown() {
    lastInteraction = millis();
    if (currentScreen == MENU)
        menuIndex = (menuIndex + 1) % menuItems;
}
