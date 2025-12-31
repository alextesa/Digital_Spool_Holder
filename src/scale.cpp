#include <Arduino.h>
#include "HX711.h"
#include "scale.h"

#define HX_DOUT 32
#define HX_SCK  33

#define DEAD_ZONE 3 // Cuanto tiene que variar el valor para que sea real

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

    // Leer solo 1 muestra por iteración
    float gramos = scale.get_units(1);

    // Promedio móvil simple
    pesoMostrado = (pesoMostrado + redondear(gramos)) / 2;

    // Aplicar DEAD_ZONE
    if (abs(pesoMostrado - redondear(gramos)) < DEAD_ZONE) return pesoMostrado;

    return pesoMostrado;
}


