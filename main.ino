//POPESCU ANDREI-LIVIU - 322AB
#include <LiquidCrystal.h>
#include "senzor_lumina.h"
#include "thermistor.h"
#include "soil.h"
#include "led.h"
Led bec;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define soil_pin 2
Soil obj3(soil_pin);

#define lumina_pin 1
Senzor_lumina obj1(lumina_pin);

#define thermistor_pin 3
Thermistor obj2(thermistor_pin);

#define buton_lux 13
uint8_t state_buton_lux = 0; //se face 1 cand este apasat butonul

#define buton_temp 5
uint8_t state_buton_temp = 0;
double temp_average = 0;

#define buton_soil 6
uint8_t state_buton_soil = 0;

#define buton_planta 4
uint8_t state_buton_planta = 0;
uint8_t alerta_apa = 0;
uint8_t alerta_lumina = 0;
uint8_t alerta_temperatura = 0;


void setup() {
    Serial.begin(19200);
    pinMode(buton_lux, INPUT_PULLUP); 
    pinMode(buton_temp, INPUT_PULLUP); 
    pinMode(buton_soil, INPUT_PULLUP); 
    pinMode(buton_planta, INPUT_PULLUP); 

    lcd.begin(16, 2); //am setat coloanele si randurile lcd-ului
    lcd.clear();
    lcd.print("Please press");
    lcd.setCursor(0, 1);
    lcd.print("a button ^_^");
    
}

void loop() {
    uint8_t i;
    
///////////////////LUX//////////////////////////////    

/////buton_state///////
    if (digitalRead(buton_lux) == LOW) {
      state_buton_lux = 1;
      state_buton_temp = 0;
      state_buton_soil = 0;
      state_buton_planta = 0;

      lcd.clear();
      lcd.print("Senzor lumina:");
      lcd.setCursor(3,1);
      lcd.print("Lux");
    }

    if (digitalRead(buton_temp) == LOW) {
      state_buton_lux = 0;
      state_buton_temp = 1;
      state_buton_soil = 0;
      state_buton_planta = 0;

      lcd.clear();
      lcd.print("Temperatura:");
      
    }

    if (digitalRead(buton_soil) == LOW) {
      state_buton_lux = 0;
      state_buton_temp = 0;
      state_buton_soil = 1;
      state_buton_planta = 0;
      lcd.clear();
      lcd.print("Soil moisture:");
      
      lcd.setCursor(3,1);
      lcd.print("%");
    }    
    if (digitalRead(buton_planta) == LOW) {
      state_buton_lux = 0;
      state_buton_temp = 0;
      state_buton_soil = 0;
      state_buton_planta = 1;
      lcd.clear();
      
    }   

/////////////////////LUX///////////////////
    if (state_buton_lux == 1) {
      lcd.setCursor(0, 1); //am setat cursorul pe coloana 0 linia 1 (linia 1 e a doua pt ca numaratoarea incepe de la 0)
      if(obj1.get_value() < 100 && obj1.get_value() > 9) {
        lcd.print(" ");
        lcd.print(obj1.get_value());

      } else if(obj1.get_value() < 10) {
          lcd.print("  ");
          lcd.print(obj1.get_value());
        } else {
          lcd.print(obj1.get_value());
        }
      
    }
    
/////////////////////TEMP/////////////////////////
    for(i = 0; i < 100; i++) {
      temp_average += obj2.calcule();
    }
    temp_average = temp_average / 100;

    if (state_buton_temp == 1) {
      
      lcd.setCursor(0, 1);
      lcd.print(temp_average);
      lcd.setCursor(4, 1);
      lcd.print("C");
      
    }

///////////////////SOIL///////////////////////////   
    if(state_buton_soil == 1) {
      lcd.setCursor(0,1);
      // lcd.print(obj3.soil_moisture());
      
      if(obj3.soil_moisture() < 100 && obj3.soil_moisture() > 9) {
        lcd.print(" ");
        lcd.print(obj3.soil_moisture());

      } else if(obj3.soil_moisture() < 10) {
          lcd.print("  ");
          lcd.print(obj3.soil_moisture());
        } else {
          lcd.print(obj3.soil_moisture());
        }
      
    }
    //////////////PLANTA_LOGIC////////////////
    if(obj3.soil_moisture() < 20) {
        alerta_apa = 1;
    } else if(obj3.soil_moisture() > 80) {
        alerta_apa = 2;
    } else {
        alerta_apa = 0;
    }

    if(temp_average < 5) {
      alerta_temperatura = 1;

    } else {
      alerta_temperatura = 0;
    }

    if(obj1.get_value() > 80 && obj1.get_value() < 130) {
      alerta_lumina = 1;
    } else {
      alerta_lumina = 0;
    }
////////ALARMA_Logic/////////
if(alerta_apa == 1 || alerta_apa == 2) {
  bec.yellow();
} else if(alerta_lumina == 1 ) {
  bec.yellow();
} else if(alerta_temperatura == 1) {
  bec.yellow();
} else bec.green();

/////////PLANTA_Buton///////
    if(state_buton_planta == 1) {
      
      if(alerta_apa == 1) {
        lcd.clear();
        lcd.print("Starea plantei:");
        lcd.setCursor(0, 1);
        lcd.print("Uda planta!");
      } else if(alerta_apa == 2) {
        lcd.clear();
        lcd.print("Starea plantei:");
        lcd.setCursor(0, 1);
        lcd.print("Prea multa apa!");
      }
      else if(alerta_temperatura == 1) {
        lcd.clear();
        lcd.print("Starea plantei:");
        lcd.setCursor(0, 1);
        lcd.print("Dead X_X");
      }
      else if(alerta_lumina == 1) {
        lcd.clear();
        lcd.print("Starea plantei:");
        lcd.setCursor(0, 1);
        lcd.print("Mai mult Soare!");
      } else {
        lcd.clear();
        lcd.print("Starea plantei:");
        lcd.setCursor(0, 1);
        lcd.print("Planta traieste ^_^");
      }
    }
    
    delay(700);
    
}
 