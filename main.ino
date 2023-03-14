#include <Servo.h>
#define black 1
#define white 0
bool finish=false;
bool localfinish=false;
int c_intersection=0;
//Creating a main class
class Robot {
  private:
  //Defining required variables
  long duration;
  int distance;
  const int leftwheel=2;
  const int rightwheel=3;
  const int ultrasonic=9;
  const int IR_ML=4;
  const int IR_MR=8;
  Servo servoLeft, servoRight;
  
  public:
  Robot();
  void INIT();
  //Declaring all the required functions
  float getDistance();
  void drive(char i);
  void displayData();
  bool linefollowing();
  void obstacledetection();
  void test();
};

//Initialization
Robot::Robot(){
  
}

void Robot::INIT(){
  servoLeft.attach(leftwheel);
  servoRight.attach(rightwheel);
}

//Defining getDistance function
float Robot::getDistance() {
  digitalWrite(ultrasonic, LOW); // set the pin to low
  delayMicroseconds(2); // wait for 2 microseconds
  digitalWrite(ultrasonic, HIGH); // set the pin to high to trigger the sensor
  delayMicroseconds(10); // wait for 10 microseconds
  digitalWrite(ultrasonic, LOW); // set the pin to low again to switch to echo mode

  duration = pulseIn(ultrasonic, HIGH); // measure the duration of the sound wave travel
  distance = duration * 0.034 / 2; // calculate the distance in cm
  
  Serial.print("Obstacles in ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

//Defining drive function
void Robot::drive(char i) {
  switch(i){
  // f, b, l, r, s means forward, backward, left, right, and stop
    case 'f':servoLeft.write(1550);servoRight.write(1450);Serial.println("f");break;
    case 'b':servoLeft.write(1450);servoRight.write(1550);break;
    case 'l':servoLeft.write(1550);servoRight.write(1550);break;
    case 'r':servoLeft.write(1450);servoRight.write(1450);break;
    case 's':servoLeft.write(1500);servoRight.write(1500);break;
    default:Serial.println("Unclear command for motors");break;
  }
}

bool Robot::linefollowing(){
  int SL = digitalRead(IR_ML);
  int SR = digitalRead(IR_MR);
  if (SL == white && SR == white) {
    //forward
    drive('f');Serial.println("Line is Centered");return true;
  }
  else if (SL == black && SR== white) {
    drive('l');Serial.println("Line is on the Left");return true;
  }
  else if (SL == white &&  SR == black) {
    // Turn right
    drive('r');Serial.println("Line is on the Right");return true;
  }
  else {
    // Stop
    drive('s');Serial.println("Intersection ahead");return false;
  }
}

//Defining displayData function
void Robot::displayData() {
  
}

void Robot::obstacledetection(){
  
}

void Robot::test(){
  servoLeft.write(1500);servoRight.write(1500);

}

//create robot object
Robot rob;

void setup() {
  //initialize objects of Robot class and calling all the functions using the created object
  Serial.begin(9600);
  rob.INIT();
}



void loop() {
  if(!finish){  //gloabal check flag, will set to be true when finish parking

    //follow the line and enter the intersection
    while(!localfinish){
      if(!rob.linefollowing()){     //if meet intersection
        rob.drive('s');delay(500);  //turn right
        rob.drive('r');delay(1000);
        localfinish=true;
        c_intersection++;  //record  the intersections have been passed
      }
    }

    //obstacle detection
    localfinish=false;
    while(!localfinish){
      
    }

    //parking section
    localfinish=false;
    while(localfinish){

    }

  }
  
}
