#include "ui.h"

// ================= VARIABLES =================
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Screen currentScreen = SPLASH;
unsigned long lastInteraction = 0;

// Menú
MenuOption currentMenu = MENU_PESO;
const char* menuText[MENU_COUNT] = { "Peso", "Calibrar", "Opciones", "Tara" };

// ================= INICIALIZACION =================
void uiInit() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Error pantalla");
        while(true); // detener para no seguir con fallos
    }
    display.clearDisplay();
    display.display();
    lastInteraction = millis();
    currentScreen = SPLASH;
}

// ================= LOOP PRINCIPAL =================
void uiLoop() {
    switch(currentScreen) {
        case SPLASH:
            renderSplash();
            if (millis() - lastInteraction > 2000) {
                currentScreen = PRINCIPAL;
                lastInteraction = millis();
            }
            break;
        case PRINCIPAL:
            renderPrincipal();
            break;
        case MENU:
            renderMenu();
            break;
    }
}

// ================= PANTALLA SPLASH =================
void renderSplash() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println("Inicializando");
    display.setCursor(0, 40);
    display.println("balanza ESP32");

    int barra = ((millis() / 200) % 6) + 1;
    for(int i=0; i<barra; i++) {
        display.fillRect(110 + i*3, 55, 2, 4, SSD1306_WHITE);
    }
    display.display();
}

// ================= PANTALLA PRINCIPAL =================
void renderPrincipal() {
    display.clearDisplay();

    int peso = leerPesoEstable();

    int16_t x, y;
    uint16_t w, h;
    String s = String(peso) + " g";

    display.setTextSize(2);
    display.getTextBounds(s, 0, 0, &x, &y, &w, &h);
    display.setCursor((SCREEN_WIDTH - w)/2, (SCREEN_HEIGHT - h)/2);
    display.setTextColor(SSD1306_WHITE);
    display.println(s);

    // Mostrar versión
    String ver = "DSH v0.3";
    display.setTextSize(1);
    display.getTextBounds(ver, 0, 0, &x, &y, &w, &h);
    display.setCursor(SCREEN_WIDTH - w - 1, SCREEN_HEIGHT - h - 1);
    display.println(ver);

    display.display();
}

// ================= MENÚ =================
void renderMenu() {
    display.clearDisplay();

    // Marco exterior
    display.drawRoundRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 5, SSD1306_WHITE);

    // Título
    display.setTextSize(1);
    display.setCursor(10, 3);
    display.print("MENU PRINCIPAL");

    // Opciones
    for(int i = 0; i < MENU_COUNT; i++) {
        int y = 15 + i * 12;
        if(i == currentMenu) {
            display.fillRoundRect(5, y-1, SCREEN_WIDTH-10, 10, 3, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
        } else {
            display.setTextColor(SSD1306_WHITE);
        }
        display.setCursor(12, y);
        display.setTextSize(1);
        display.print(menuText[i]);
    }

    display.display();
}

// ================= NAVEGACIÓN =================
void menuUp() {
    if(currentMenu == 0) currentMenu = (MenuOption)(MENU_COUNT - 1);
    else currentMenu = (MenuOption)(currentMenu - 1);
}

void menuDown() {
    currentMenu = (MenuOption)((currentMenu + 1) % MENU_COUNT);
}

MenuOption menuSelect() {
    return currentMenu;
}
