#include <Servo.h>

const int SigPin = 9;
float invcmCosnt = (2*1000000)/(100*344.8); //cmDist=rawTime/invcmCosnt
float invinCosnt = invcmCosnt*2.54; //inDist=rawTime/invinCosnt
unsigned long startTime;
unsigned long endTime;
long object_length;

// Defining values for black and white
#define black 1
#define white 0

// IR sensor pins
const int IR_M1 = 4;   //D4
const int IR_M2 = 8;   //D8

// Creating servo objects
Servo servoLeft, servoRight;

void setup() {
  Serial.begin(9600);
  servoLeft.attach(2);
  servoRight.attach(3);
}

void loop() {
  // Read the sensor values
  int S1 = digitalRead(IR_M1);
  int S2 = digitalRead(IR_M2);
  
  lane_motion();
  

  //Conditions to drive line folower appropriately
  if (S1 == white && S2 == white) {
    //forward
    servoLeft.write(1550);
    servoRight.write(1450);
    
    if(detectObstacle() < 300) {
      startTime = millis();
      while(detectObstacle() < 300) {
      };
      endTime = millis();
      object_length = endTime - startTime;
      Serial.println(object_length);
    }
    else {
      servoLeft.write(1550);
      servoRight.write(1450);
    }
  }
  else if (S1 == black &&  S2 == black) {
    servoLeft.write(1550);
    servoRight.write(1450);
    delay(500);
    servoLeft.write(1550);
    servoRight.write(1550);
    delay(2000);
    servoLeft.write(1550);
    servoRight.write(1450);
  }
  else {
    servoLeft.write(1500);
    servoRight.write(1500);
  }
}

// Function for obtaining ultrasonic sensor readings
float detectObstacle() {
  float rawTime, inDist, inDist1, cmDist, cmDist1; //declare variables
  /* Ping))) produces chirp when a HIGH pulse of 2us (min) or longer duration (5us typical) is
  applied to Sig pin. To have a clarn HIGH pulse, give a low and then high */
  pinMode(SigPin, OUTPUT);
  digitalWrite(SigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(SigPin, LOW);
  /* Now same Sign pin is to be used to monitor if the return echo has been received. Essentially,
  Sig pin remains HIGH until a return echo is received and at that time it goes LOW. So measure
  the time duration for HIGH at the Sig pin */
  pinMode(SigPin, INPUT);
  rawTime = pulseIn(SigPin, HIGH); //measured in u-seconds
  cmDist = rawTime/invcmCosnt;
  //Serial.print(cmDist);
  //Serial.println("cm, ");
  return cmDist;
}

void lane_motion() {
  if (S1 == white && S2 == white) {
    //forward
    servoLeft.write(1550);
    servoRight.write(1450);
  }
  else if (S1 == black &&  S2 == black) {
    servoLeft.write(1550);
    servoRight.write(1450);
    delay(500);
    servoLeft.write(1550);
    servoRight.write(1550);
    delay(2000);
    servoLeft.write(1550);
    servoRight.write(1450);
  }
  else {
    servoLeft.write(1500);
    servoRight.write(1500);
  }
}

