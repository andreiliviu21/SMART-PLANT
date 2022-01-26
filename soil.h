#ifndef ARDUINO_SOIL_H
#define ARDUINO_SOIL_H
#include <Arduino.h>

class Soil  {
private:
	byte pin;
	const int AirValue;
	const int WaterValue;
	int soilMoistureValue;
	int soilmoisturepercent;
public:
	Soil(byte pin);
	int soil_moisture();
	// int soil_percent();

};
#endif
