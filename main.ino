//Defining all the pins for sensors and wheels
#define black 1
#define white 0
//Creating a main class
class Robot {
  private:
  //Defining required variables
  long duration;
  int distance;
  const int leftwheel=2
  const int rightwheel=3;
  const int ultrasonic=9;
  const int IR_ML=4;
  const int IR_MR=8;
  Servo servoLeft, servoRight;
  
  public:
  Robot();
  //Declaring all the required functions
  void getDistance();
  float driveRobot();
  void displayData();
  void linefollowing();
};

//Initialization
Robot::Robot(){
  servoLeft.attach(leftwheel);
  servoRight.attach(rightwheel);  
}

//Defining getDistance function
float Robot::getDistance() {
  digitalWrite(pin, LOW); // set the pin to low
  delayMicroseconds(2); // wait for 2 microseconds
  digitalWrite(pin, HIGH); // set the pin to high to trigger the sensor
  delayMicroseconds(10); // wait for 10 microseconds
  digitalWrite(pin, LOW); // set the pin to low again to switch to echo mode

  duration = pulseIn(pin, HIGH); // measure the duration of the sound wave travel
  distance = duration * 0.034 / 2; // calculate the distance in cm
  
  Serial.print("Obstacles in ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

//Defining driveRobot function
void Robot::driveRobot(char i) {
  switch(i){
  // f, b, l, r, s means forward, backward, left, right, and stop
    case 'f':servoLeft.write(1550);servoRight.write(1450);break;
    case 'b':servoLeft.write(1450);servoRight.write(1550);break;
    case 'l':servoLeft.write(1550);servoRight.write(1550);break;
    case 'r':servoLeft.write(1450);servoRight.write(1450);break;
    case 's':servoLeft.write(1500);servoRight.write(1500);break;
    default:Serial.println("Unclear command for motors");break;
  }
}

void linefollowing(){
  SL = digitalRead(IR_ML);
  SR = digitalRead(IR_MR);
  if (SL == white && SR == white) {
    //forward
    dirveRobot('f');
  }
  else if (SL == black && SR== white) {
    driveRobot('l');
  }
  else if (SL == white &&  SR == black) {
    // Turn right
    driveRobot('r');
  }
  else {
    // Stop
    servoLeft.write(1500);
    servoRight.write(1500);
  }
}

//Defining displayData function
void Robot::displayData() {
  
}


void setup() {
  //Creating objects of Robot class and calling all the functions using the created object
  Serial.begin(9600);
  Robot rob;
}

void loop() {
 rob.linefollowing();
}
