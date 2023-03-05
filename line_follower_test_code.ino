#include <QTRSensors.h>
#include <Servo.h>

QTRSensorsRC qtrrc((unsigned char[]) {2, 3, 4, 5, 6, 7, 8, 9}, 8);
unsigned int sensorValues[8];

#define MOTOR_LEFT_PIN 10
#define MOTOR_RIGHT_PIN 11

#define MAX_SPEED 150
#define MIN_SPEED 50
#define THRESHOLD 500

void setup() {
  qtrrc.calibrate();
  pinMode(MOTOR_LEFT_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_PIN, OUTPUT);
}

void loop() {
  qtrrc.read(sensorValues);
  int error = qtrrc.readLine(sensorValues);

  int leftSpeed = MAX_SPEED;
  int rightSpeed = MAX_SPEED;
  
  if (error < 0) {
    leftSpeed = MIN_SPEED;
  } else if (error > 0) {
    rightSpeed = MIN_SPEED;
  }

  int diff = abs(error);
  if (diff > THRESHOLD) {
    leftSpeed = 0;
    rightSpeed = 0;
  } else {
    int speedDelta = map(diff, 0, THRESHOLD, 0, MAX_SPEED - MIN_SPEED);
    if (error < 0) {
      leftSpeed -= speedDelta;
    } else {
      rightSpeed -= speedDelta;
    }
  }

  // set motor speed and direction
  if (leftSpeed == 0 && rightSpeed == 0) {
    // stop the robot
    analogWrite(MOTOR_LEFT_PIN, 0);
    analogWrite(MOTOR_RIGHT_PIN, 0);
  } else {
    // drive the motors
    if (error < 0) {
      // turn left
      analogWrite(MOTOR_LEFT_PIN, leftSpeed);
      analogWrite(MOTOR_RIGHT_PIN, rightSpeed);
    } else if (error > 0) {
      // turn right
      analogWrite(MOTOR_LEFT_PIN, leftSpeed);
      analogWrite(MOTOR_RIGHT_PIN, rightSpeed);
    } else {
      // go straight
      analogWrite(MOTOR_LEFT_PIN, leftSpeed);
      analogWrite(MOTOR_RIGHT_PIN, rightSpeed);
    }
  }
}




