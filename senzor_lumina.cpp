#include "senzor_lumina.h"  

Senzor_lumina::Senzor_lumina(byte pin) {
    reading = 0;
    this->pin = pin;
    
}

int Senzor_lumina::get_value() {
    reading  = analogRead(pin);
    return reading;
}


