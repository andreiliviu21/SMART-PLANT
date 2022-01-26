#include "soil.h"  

Soil::Soil(byte pin): AirValue(600), WaterValue(350) {
    this->pin = pin;
    soilmoisturepercent = 0;
    soilMoistureValue = 0;
}

int Soil::soil_moisture() {
    soilMoistureValue = analogRead(pin);
    soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    if(soilmoisturepercent >= 100) {
        return 100;
    } else if(soilmoisturepercent <=0) {
        return 0;
    } else if(soilmoisturepercent >0 && soilmoisturepercent < 100) {
        return soilmoisturepercent;
    }

}