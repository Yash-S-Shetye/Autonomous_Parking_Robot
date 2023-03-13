#include <Servo.h>
Servo servoLeft, servoRight; 
int pos = 0;
void setup() {
  // The servo control wire is connected to Arduino D2 and D4 pin.
  servoLeft.attach(2);
  servoRight.attach(3);
}

void loop() {
  // Forward
  servoLeft.write(1550);
  servoRight.write(1450);
  delay(1000);

  // Stop
  servoLeft.write(1500);
  servoRight.write(1500);
  delay(1000);
  
  // Backward
  servoLeft.write(1450);
  servoRight.write(1550);
  delay(1000);

  // Stop
  servoLeft.write(1500);
  servoRight.write(1500);
  delay(1000);

  // Left
  servoLeft.write(1450);
  servoRight.write(1450);
  delay(1000);

  // Stop
  servoLeft.write(1500);
  servoRight.write(1500);
  delay(1000);
  
  // Right
  servoLeft.write(1550);
  servoRight.write(1550);
  delay(1000);

  // Stop
  servoLeft.write(1500);
  servoRight.write(1500);
  delay(1000);
}
