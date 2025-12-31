#include "ui.h"
#include "scale.h"  // tu módulo de balanza

// ================= VARIABLES =================
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Screen currentScreen = SPLASH;
unsigned long lastInteraction = 0;

// ================= INICIALIZACION =================
void uiInit() {

    //Verificamos que la pantalla inicie
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
    }
}

// ================= PANTALLA INICIAL =================
void renderSplash() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println("Inicializando");
    display.setCursor(0, 40);
    display.println("balanza ESP32");

    // Barra de carga
    int barra = ((millis() / 200) % 6) + 1;
    for(int i=0; i<barra; i++) {
        display.fillRect(110 + i*3, 55, 2, 4, SSD1306_WHITE);
    }

    display.display();
}

// ================= PANTALLA PRINCIPAL =================
void renderPrincipal() {
    display.clearDisplay();

    int peso = leerPesoEstable();  // tu función de balanza

    int16_t x, y;
    uint16_t w, h;

    // Mostrar peso centrado
    String s = String(peso) + "g";
    display.setTextSize(2);
    display.getTextBounds(s, 0, 0, &x, &y, &w, &h);
    display.setCursor((SCREEN_WIDTH - w)/2, (SCREEN_HEIGHT - h)/2);
    display.setTextColor(SSD1306_WHITE);
    display.println(s);

    // Mostrar versión abajo a la derecha
    String ver = "DSH v.01";
    display.setTextSize(1);
    display.getTextBounds(ver, 0, 0, &x, &y, &w, &h);
    display.setCursor(SCREEN_WIDTH - w - 1, SCREEN_HEIGHT - h - 1);
    display.println(ver);

    display.display();
}

