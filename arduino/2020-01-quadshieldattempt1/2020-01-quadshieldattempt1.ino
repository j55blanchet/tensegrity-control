#include <Encoder.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

//
// Serial control sketch of a 3 bar tensegrity.
//
// Controls:
//    Usage: enter commands in serial monitor.
//    'q', 'w', 'e' - select motor 1/2/3
//    'a', 's'      - set lower/upper bound of selected motor
//    <number>      - set speed of selected motor
//    'f', 'b'      - set direction (forward / backward) of selected motor
//
//    System status will be printed after every newline
//       > Note: ensure baud rate in serial monitor is 19200

// Pins that the encoder is attached to.
#define ENCODER_A1 11
#define ENCODER_B1 12
#define ENCODER_A2   4
#define ENCODER_B2   3
#define ENCODER_A3   6
#define ENCODER_B3   7

// Speeds of the 3 motors
int16_t speed1 = 0;
int16_t speed2 = 0;
int16_t speed3 = 0;

// Serial input buffer
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
int min1 = 0;
int min2 = 0;
int min3 = 0;
int max1 = 0;
int max2 = 0;
int max3 = 0;
int* selected_min = &min1;
int* selected_max = &max1;
int* selected_count = &counts1;

Adafruit_DCMotor *selectedMotor = motor1;
uint8_t *selectedDir = &dir1;
int16_t *selectedSpeed = &speed1;

// FOR FUTURE WORK - sets the encoder so that 0 is the midpoint of the 
//                   range of the mechanism
// 
//void setBounds() {
//  int enc1Range = max1 - min1;
//  int curPos = counts1 - (min1 / 2 + max1 / 2);
//  max1 = enc1Range / 2;
//  min1 = -max1;
//  enc1.write(curPos);
//}

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
  motor2->run(FORWARD);
  motor3->run(FORWARD);

  // Zero out the encoder
  enc1.write(0);
  enc2.write(0);
  enc3.write(0);
}

void loop() {

  counts1 = enc1.read();
  counts2 = enc2.read();
  counts3 = enc3.read();

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
      selected_min = &min1;
      selected_max = &max1;
      selected_count = &counts1;
      Serial.println("Motor 1 Selected");
    }
    if( (char) inChar == 'w') {
      selectedMotor = motor2;
      selectedDir = &dir2;
      selectedSpeed = &speed2;
      selected_min = &min2;
      selected_max = &max2;
      selected_count = &counts2;
      Serial.println("Motor 2 Selected");
    }
    if( (char) inChar == 'e') {
      selectedMotor = motor3;
      selectedDir = &dir3;
      selectedSpeed = &speed3;
      selected_min = &min3;
      selected_max = &max3;
      selected_count = &counts3;
      Serial.println("Motor 3 Selected");
    }

    if( (char) inChar == 'a') {
      *selected_min = *selected_count;
    }
    if( (char) inChar == 's') {
      *selected_max = *selected_count;
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

void print_motor_status(int i, Adafruit_DCMotor* motor, uint8_t dir, int count, int16_t motorSpeed, int count_min, int count_max) {
  if (motor == selectedMotor)
    Serial.print("*");
  else
    Serial.print(" ");
  
  Serial.print("Motor ");
  Serial.print(i);  
  Serial.print(": ");
  Serial.print(count);
  Serial.print("  (");
  Serial.print(count_min);
  Serial.print(", ");
  Serial.print(count_max);
  Serial.print(") ");
  Serial.print(" @ ");

  if (dir == FORWARD)
    Serial.print("+");
  else
    Serial.print("-");
    
  Serial.println(motorSpeed);
}

void print_status() {
  print_motor_status(1, motor1, dir1, counts1, speed1, min1, max1);
  print_motor_status(2, motor2, dir2, counts2, speed2, min2, max2);
  print_motor_status(3, motor3, dir3, counts3, speed3, min3, max3);
}
