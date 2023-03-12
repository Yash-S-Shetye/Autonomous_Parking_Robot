// Line follower test code

#include <Servo.h>

// Defining values for black and white
#define black 1
#define white 0

// IR sensor pins
const int IR_M1 = 4;   //D4
const int IR_M2 = 8;   //D8

Servo servoLeft, servoRight;

void setup() {
  servoLeft.attach(2);
  servoRight.attach(3);
}
void loop() {

  // Read the sensor values
  int S1 = digitalRead(IR_M1);
  int S2 = digitalRead(IR_M2);
  int S3 = digitalRead(IR_EL);
  int S4 = digitalRead(IR_ER);

  //Conditions to drive line folower appropriately
  if (S1 == white && S2 == white) {
    //forward
    servoLeft.write(1550);
    servoRight.write(1450);
  }
  else if (S1 == black &&  S2 == black) {
    // Turn right
    servoLeft.write(1550);
    servoRight.write(1520);
    delay(1000);
  }
  else {
    // Stop
    servoLeft.write(1500);
    servoRight.write(1500);
  }
}




