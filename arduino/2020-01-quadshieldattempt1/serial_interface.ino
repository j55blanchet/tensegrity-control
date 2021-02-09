//void print_motor_status(int i, Adafruit_DCMotor* motor, uint8_t dir, int count, int16_t motorSpeed, int count_min, int count_max) {
//  if (motor == selectedMotor)
//    Serial.print("*");
//  else
//    Serial.print(" ");
//  
//  Serial.print("Motor ");
//  Serial.print(i);  
//  Serial.print(": ");
//  Serial.print(count);
//  Serial.print("  (");
//  Serial.print(count_min);
//  Serial.print(", ");
//  Serial.print(count_max);
//  Serial.print(") ");
//  Serial.print(" @ ");
//
//  if (dir == FORWARD)
//    Serial.print("+");
//  else
//    Serial.print("-");
//    
//  Serial.println(motorSpeed);
//}
//
//
//void print_status() {
//  print_motor_status(1, motor1, dir1, counts1, speed1, min1, max1);
//  print_motor_status(2, motor2, dir2, counts2, speed2, min2, max2);
//  print_motor_status(3, motor3, dir3, counts3, speed3, min3, max3);
//}
