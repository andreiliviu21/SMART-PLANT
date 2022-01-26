#include "thermistor.h"  

Thermistor::Thermistor(byte pin) {
    this->pin = pin;
    R1 = 10000;
    c1 = 1.009249522e-03;
    c2 = 2.378405444e-04;
    c3 = 2.019202697e-07;
}

float Thermistor::calcule() {
    Vo = analogRead(pin);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    Tc = T - 273.15;
    return Tc;
}