#include <Servo.h>
Servo servoLeft, servoRight; 
int pos = 0;
void setup() {
  // The servo control wire is connected to Arduino D2 and D4 pin.
  servoLeft.attach(2);
  servoRight.attach(4);
  
  servoLeft.write(90);
  servoRight.write(90);
}

void loop() {
  // Left wheel servo spin forward while right wheel servo spins backward at full speed for 1 second
  servoLeft.write(1500);
  servoLeft.write(0);
  delay(1000);
  // Both servos are stationary for 1 second.
  servoLeft.write(90);
  servoRight.write(90);
  delay(1000);
  // Right wheel servo spin forward while left wheel servo spins backward at full speed for 1 second
  servoLeft.write(0);
  servoRight.write(1500);
  delay(1000);
  // Both servos are stationary for 1 second.
  servoLeft.write(90);
  servoRight.write(90);
  delay(1000);
}
