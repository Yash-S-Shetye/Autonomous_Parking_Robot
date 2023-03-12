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
  float driveRobot();
  void displayData();
};

//Initialization
Robot::Robot(){
  servoLeft.attach(leftwheelpin);
  servoRight.attach(rightwheelpin);  
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
