#include "Mobita.h"

#define PWM_A 3
#define PWM_B 9
#define PWM_C 10
#define PWM_D 11

const uint8_t AF {A1}, AB {A2}, BF {4}, BB {5}, CF {6}, CB {7}, DF {8}, DB {12}; 
Mobita mobita(PWM_A, PWM_B, PWM_C, PWM_D, AF, AB, BF, BB, CF, CB, DF, DB);

int isSRead = 0;
String stringSRead = ""; char s_read = 0; 
unsigned long serialUpdateTime = millis();
uint8_t updateTime = 100;

void readSerial(){
  while(Serial.available()>0){
    s_read = Serial.read();
    if (!((s_read <= 0) || (s_read == '\r') || (s_read == '\n'))){
      stringSRead += s_read;
      isSRead++;
    }
  }
}

void setup() {}

void loop() {
  if(millis() - serialUpdateTime >= updateTime){
    readSerial();
    serialUpdateTime = millis();
  }

  if (isSRead){
    // write to serial.
    Serial.print("Received: <<"); Serial.print(stringSRead); Serial.print(">> ");
    
    // execute action.


    // reset indicators.
    isSRead = 0; stringSRead = "";
  }
}
