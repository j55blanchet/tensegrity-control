#include <Encoder.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Pins that the encoder is attached to.
#define ENCODER_A1 11
#define ENCODER_B1 12
#define ENCODER_A2   4
#define ENCODER_B2   3
#define ENCODER_A3   6
#define ENCODER_B3   7

int16_t speed1 = 0;
int16_t speed2 = 0;
int16_t speed3 = 0;

String inString = "";

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);

Encoder enc1(ENCODER_A1, ENCODER_B1);
Encoder enc2(ENCODER_A2, ENCODER_B2);
Encoder enc3(ENCODER_A3, ENCODER_B3);

int counts1 = 0;
int counts2 = 0;
int counts3 = 0;
uint8_t dir1 = FORWARD;
uint8_t dir2 = FORWARD;
uint8_t dir3 = FORWARD;

Adafruit_DCMotor *selectedMotor = motor1;
uint8_t *selectedDir = &dir1;
int16_t *selectedSpeed = &speed1;

void setup() {

  Serial.begin(19200);
  while(!Serial) {
    ;
  }
  Serial.println("Dartmouth Tensegrity - 3 Bar Test");

  AFMS.begin();
  
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  motor3->setSpeed(0);

  motor1->run(FORWARD);
//  motor1->run(RELEASE);
  motor2->run(FORWARD);
//  motor2->run(RELEASE);
  motor3->run(FORWARD);
//  motor3->run(RELEASE);

  // Zero out the encoder
  enc1.write(0);
  enc2.write(0);
  enc3.write(0);
}



void loop() {

  counts1 = enc1.read();
  counts2 = enc2.read();
  counts3 = enc3.read();

//  motor1->run(dir1);
//  motor2->run(dir2);
//  motor3->run(dir3);
//  motor1->setSpeed(speed1);
//  motor2->setSpeed(speed2);
//  motor3->setSpeed(speed3);


  if (Serial.available() > 0) {
    int inChar = Serial.read();

    if( (char) inChar == 'f') {
      *selectedDir = FORWARD;
      selectedMotor->run(*selectedDir);
      Serial.println("Forward");
    }
    if( (char) inChar == 'b') {
      *selectedDir = BACKWARD;
      selectedMotor->run(*selectedDir);
      Serial.println("Backward");
    }

    if( (char) inChar == 'q') {
      selectedMotor = motor1;
      selectedDir = &dir1;
      selectedSpeed = &speed1;
      Serial.println("Motor 1 Selected");
    }
    if( (char) inChar == 'w') {
      selectedMotor = motor2;
      selectedDir = &dir2;
      selectedSpeed = &speed2;
      Serial.println("Motor 2 Selected");
    }
    if( (char) inChar == 'e') {
      selectedMotor = motor3;
      selectedDir = &dir3;
      selectedSpeed = &speed3;
      Serial.println("Motor 3 Selected");
    }
    
    if (isDigit(inChar)) {
      inString += (char) inChar;
    }
    if(inChar == '\n') {

      if(inString.length() > 0) {
        Serial.print("Receieved Speed: ");
        Serial.println(inString.toInt());
        *selectedSpeed = inString.toInt();
        selectedMotor->setSpeed(*selectedSpeed);
        inString = "";
      }

      print_status();
    }
  }
}
