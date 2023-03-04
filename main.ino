//Defining all the pins for sensors and wheels
#define trigpin 9
#define echopin 10
#define leftwheel 5
#define rightwheel 6
//Creating a main class
class Robot {
  private:
  //Defining required variables
  long duration;
  int distance;
  
  public:
  //Declaring all the required functions
  void getDistance();
  void driveRobot();
  void displayData();
};

//Defining getDistance function
void Robot::getDistance() {
  
}

//Defining driveRobot function
void Robot::driveRobot() {
  
}

//Defining displayData function
void Robot::displayData() {
  
}


void setup() {
  //Creating objects of Robot class and calling all the functions using the created object
  Robot obj;
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  Serial.begin(9600);
}

void loop() {

}
