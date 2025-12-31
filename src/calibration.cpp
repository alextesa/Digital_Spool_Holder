#include "calibration.h"
#include "scale_ctrl.h"
#include <Arduino.h>

static CalState calState = CAL_TARA;
static float pesoRef = 236.0;
static long rawTara = 0;

CalState getCalState() { return calState; }

void calInit(float ref) {
    pesoRef = ref;
    calState = CAL_TARA;
}

void calNextStep() {
    switch (calState) {
        case CAL_TARA:
            scale.tare();
            rawTara = leerRawPromedioCal(20);
            calState = CAL_PESO_REF;
            break;

        case CAL_PESO_REF: {
            long raw = leerRawPromedioCal(20);
            float factor = (raw - rawTara) / pesoRef;
            setScaleFactor(factor);
            calState = CAL_GUARDAR;
            break;
        }

        case CAL_GUARDAR:
            guardarFactorEEPROM(getScaleFactor());
            calState = CAL_FINALIZADO;
            break;

        case CAL_FINALIZADO:
            break;
    }
}
