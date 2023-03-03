#include <Servo.h>
Servo servoLeft, servoRight; 
int pos = 0;
void setup() {
  // The servo control wire is connected to Arduino D2 and D4 pin.
  servoLeft.attach(2);
  servoRight.attach(4);
  
  servoLeft.write(750);
  servoRight.write(750);
}

void loop() {
  // Both servos spin forward at full speed for 1 second.
  servoLeft.write(1300);
  servoLeft.write(1700);
  delay(1000);
  // Both servos are stationary for 1 second.
  servoLeft.write(750);
  servoRight.write(750);
  delay(1000);
  // Both servos spin in reverse at full speed for 1 second.
  servoLeft.write(1700);
  servoRight.write(1300);
  delay(1000);
  // Both servos are stationary for 1 second.
  servoLeft.write(750);
  servoRight.write(750);
  delay(1000);
}
