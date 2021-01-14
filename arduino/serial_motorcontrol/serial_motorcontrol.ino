#include <DualMAX14870MotorShield.h>
// See: https://github.com/pololu/dual-max14870-motor-shield

DualMAX14870MotorShield motors;

int16_t m1_speed = 0;
int16_t m2_speed = 0;

String inString = "";

void setup() {
//  motors.flipM1(true);
//  motors.flipM2(true);

  Serial.begin(9600);
  while(!Serial) {
    ;
  }
  
  motors.enableDrivers();
  
}


void loop() {
//  motors.setM1Speed(m1_speed);  
  motors.setM2Speed(m1_speed);

  if (Serial.available() > 0) {
    int inChar = Serial.read();
    if( (char) inChar == '-') {
      inString += (char) inChar;
    }
    if (isDigit(inChar)) {
      inString += (char) inChar;
    }
    if(inChar == '\n') {
      Serial.print("Receieved: ");
      Serial.println(inString.toInt());

      m1_speed = inString.toInt();
      inString = "";
    }
  }
}
