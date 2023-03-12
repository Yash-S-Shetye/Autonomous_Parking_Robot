//Defining all the pins for sensors and wheels
//Creating a main class
class Robot {
  private:
  //Defining required variables
  long duration;
  int distance;
  const int leftwheelpin=5;
  const rightwheelpin=6
  int ultrasonic=9;
  Servo servoLeft, servoRight;
  
  public:
  Robot();
  //Declaring all the required functions
  void getDistance();
  void driveRobot();
  void displayData();
};

//Initialization
Robot::Robot(){
  servoLeft.attach(leftwheelpin);
  servoRight.attach(rightwheelpin);  
}

//Defining getDistance function
void Robot::getDistance() {
  
}

//Defining driveRobot function
void Robot::driveRobot(char i) {
  switch(i){
  // f, b, l, r, s means forward, backward, left, right, and stop
    case 'f':servoLeft.write(1550);servoRight.write(1450);break;
    case 'b':servoLeft.write(1450);servoRight.write(1550);break;
    case 'l':servoLeft.write(1550);servoRight.write(1500);break;
    case 'r':servoLeft.write(1500);servoRight.write(1550);break;
    case 's':servoLeft.write(1500);servoRight.write(1500);break;
    default:Serial.println("Unclear command for motors");break;
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
 
}
