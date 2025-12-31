#ifndef CALIBRATION_H
#define CALIBRATION_H

enum CalState {
    CAL_TARA,
    CAL_PESO_REF,
    CAL_AJUSTE,
    CAL_GUARDAR,
    CAL_FINALIZADO
};

void calInit(float ref);
void calNextStep();
CalState getCalState();

#endif

