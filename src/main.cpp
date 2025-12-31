#include <Arduino.h>
#include "scale_ctrl.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Balanza iniciando...");
  scaleInit();
}

void loop() {
  int peso = leerPesoEstable();

  Serial.print("Peso: ");
  Serial.print(peso);
  Serial.println(" g");

  delay(300);
}
