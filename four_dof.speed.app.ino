// soft start
// soft stop.
#include "Mobita.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  //analogWrite(3, 7);
  digitalWrite(4, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i {0};
  for (; i < 256; i++){
    analogWrite(3, i);
    delay(1);
  }
  for (; i >= 0; i--){
    analogWrite(3, i);
    delay(1);
  }

}
