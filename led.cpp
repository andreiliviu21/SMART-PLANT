#include "Led.h"  

Led::Led() {

    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);

}

void Led::green(){
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, LOW);

}
void Led::yellow() {
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, HIGH);
}

