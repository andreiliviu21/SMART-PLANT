
#ifndef ARDUINO_THERMISTOR_H
#define ARDUINO_THERMISTOR_H
#include <Arduino.h>

class Thermistor   {
private:
	byte pin;
	int Vo;
    float R1;
    float logR2, R2, T, Tc;
    float c1, c2, c3;
public:
	Thermistor(byte pin);
	float calcule();
	

};
#endif
