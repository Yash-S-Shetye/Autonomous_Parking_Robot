#include 
Servo myservo1, myservo2; 
int pos = 0;
void setup() {
  // The servo control wire is connected to Arduino D2 and D4 pin.
  myservo1.attach(2);
  myservo2.attach(4);
  // Servo is stationary.
  myservo1.write(90);
  myservo2.write(90);
}

void loop() {
  // Both servos spin forward at full speed for 1 second.
  myservo.write(180);
  myservo.write(180);
  delay(1000);
  // Both servos are stationary for 1 second.
  myservo.write(90);
  myservo.write(90);
  delay(1000);
  // Both servos spin in reverse at full speed for 1 second.
  myservo.write(0);
  myservo.write(0);
  delay(1000);
  // Both servos are stationary for 1 second.
  myservo.write(90);
  myservo.write(90);
  delay(1000);
}
