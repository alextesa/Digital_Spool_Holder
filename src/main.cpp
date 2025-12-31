#include <Arduino.h>
#include "scale_ctrl.h"
#include "ui.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Balanza iniciando...");
   scaleInit();   // Inicializa la balanza
   uiInit();      // Inicializa la pantalla
}

void loop() {
  int peso = leerPesoEstable();
  uiLoop();
  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");

  delay(300);
}
