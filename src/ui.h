#ifndef UI_H
#define UI_H

#include <Arduino.h>

enum Screen {
    PRINCIPAL,
    MENU,
    CALIBRAR,
    PERFILES
};

void uiInit();
void uiLoop();

void renderPeso();
void renderMenu();
void renderCalibrar();
void renderPerfiles();

void handleSelect();
void handleUp();
void handleDown();

extern Screen currentScreen;
extern unsigned long lastInteraction;
extern int menuIndex;

#endif
