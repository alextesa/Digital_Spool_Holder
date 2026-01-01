#include <Arduino.h>
#include "scale.h"
#include "ui.h"
#include "input.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Balanza iniciando...");
   scaleInit();   // Inicializa la balanza
   uiInit();      // Inicializa la pantalla
   inputInit();    // Inicializa los botones
}

unsigned long lastUpdate = 0;
const unsigned long updateInterval = 500; // actualizar cada 500 ms

void loop() {
    unsigned long now = millis();

    // Actualizar peso y UI cada updateInterval
    if (now - lastUpdate >= updateInterval) {
        lastUpdate = now;

        int peso = leerPesoEstable();
        uiLoop();

        //Aqui puedo meter serial a debug general
        /* Serial.print("Peso: ");
        Serial.print(peso);
        Serial.println(" g"); */
        Serial.print("SCREEN = ");
        Serial.println(currentScreen);
    }

    // checkButtons siempre activo sin bloquear
    checkButtons();
}

