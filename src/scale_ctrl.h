#ifndef SCALE_CTRL_H
#define SCALE_CTRL_H

#include <HX711.h>

extern HX711 scale;

void scaleInit();
float leerPesoFiltrado();
long leerRaw();
long leerRawPromedio(int n);
long leerRawPromedioCal(int n);

void setScaleFactor(float f);
float getScaleFactor();
void resetTara();

void guardarFactorEEPROM(float f);
float cargarFactorEEPROM();

#endif
