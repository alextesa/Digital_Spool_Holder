#include <Arduino.h>
#include "HX711.h"
#include "scale_ctrl.h"

#define HX_DOUT 32
#define HX_SCK  33

#define DEAD_ZONE 5
#define MUESTRAS 25

HX711 scale;

float factorEscala = 410.0;
int pesoMostrado = 0;

long leerRawPromedio(int muestras) {
  long suma = 0;
  for (int i = 0; i < muestras; i++) {
    suma += scale.read();
  }
  return suma / muestras;
}

int redondear(float valor) {
  return (int)(valor + (valor >= 0 ? 0.5 : -0.5));
}

void scaleInit() {
  scale.begin(HX_DOUT, HX_SCK);

  delay(500);

  scale.set_scale(factorEscala);  // 👈 AQUI
  scale.tare(20);                 // 👈 PROMEDIO REAL

  Serial.println("[SCALE] Tara aplicada");
}

int leerPesoEstable() {
  if (!scale.is_ready()) return pesoMostrado;

  float gramos = scale.get_units(MUESTRAS);
  int pesoActual = redondear(gramos);

  if (abs(pesoActual - pesoMostrado) >= DEAD_ZONE) {
    pesoMostrado = pesoActual;
  }

  return pesoMostrado;
}

