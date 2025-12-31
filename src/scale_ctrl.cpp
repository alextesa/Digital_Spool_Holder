#include "scale_ctrl.h"
#include <EEPROM.h>

HX711 scale;
static float scaleFactor = 418.0;

void scaleInit() {
    scale.begin(32, 33);
    scaleFactor = cargarFactorEEPROM();
    scale.set_scale(scaleFactor);
    scale.tare();
}

float leerPesoFiltrado() {
    return scale.get_units(5);
}

long leerRaw() {
    return scale.read();
}

long leerRawPromedio(int n) {
    long sum = 0;
    for (int i = 0; i < n; i++) sum += scale.read();
    return sum / n;
}

long leerRawPromedioCal(int n) {
    return leerRawPromedio(n);
}

void setScaleFactor(float f) {
    scaleFactor = f;
    scale.set_scale(scaleFactor);
}

float getScaleFactor() {
    return scaleFactor;
}

void resetTara() {
    scale.tare();
}

void guardarFactorEEPROM(float f) {
    EEPROM.begin(32);
    EEPROM.put(0, f);
    EEPROM.commit();
}

float cargarFactorEEPROM() {
    EEPROM.begin(32);
    float f;
    EEPROM.get(0, f);
    return (isnan(f) || f == 0) ? 418.0 : f;
}
