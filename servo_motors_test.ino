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
  servoLeft.write(1700);
  servoRight.write(1300);
  delay(1000);

  // Both wheel servos stop for 1 second
  servoLeft.write(1500);
  servoRight.write(1500);
  delay(1000);
  
  // Right wheel servo spin forward while left wheel servo spins backward at full speed for 1 second
  servoLeft.write(1300);
  servoRight.write(1700);
  delay(1000);

  // Both wheel servos stop for 1 second
  servoLeft.write(1500);
  servoRight.write(1500);
  delay(1000);
}
