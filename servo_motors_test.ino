#include <Servo.h>
Servo servoLeft, servoRight; 
int pos = 0;
void setup() {
  // The servo control wire is connected to Arduino D2 and D4 pin.
  servoLeft.attach(2);
  servoRight.attach(4);
}

void loop() {
  // Left wheel servo spin forward while right wheel servo spins backward at full speed for 1 second
  servoLeft.write(100);
  servoRight.write(50);
  delay(1000);
}
