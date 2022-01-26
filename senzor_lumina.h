#ifndef ARDUINO_SENZOR_LUMINA_H
#define ARDUINO_SENZOR_LUMINA_H
#include <Arduino.h>
#include <LiquidCrystal.h>

class Senzor_lumina {
private:
	byte pin;
	int reading;

public:
	Senzor_lumina(byte pin);
	int get_value();
	
	

};
#endif
