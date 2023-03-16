#include <Servo.h>
#define black 1
#define white 0
#define obsdistance 
bool finish=false;
bool localfinish=false;
int c_intersection=0;
int parkinglot[8]={0,0,0,0,0,0,0,0};
int parkidx=0;
//Creating a robot class containing all the functions will be used
class Robot {
  private:
  //Defining required variables
  const int leftwheel=2;
  const int rightwheel=3;
  const int ultrasonic=9;
  const int IR_ML=4;
  const int IR_MR=8;
  Servo servoLeft, servoRight;
  
  public:
  void INIT();
  //Declaring all the required functions
  bool isobstacle();
  void drive(char i);
  void display();
  bool linefollowing();
  void test();
};

//Initialization
void Robot::INIT(){
  servoLeft.attach(leftwheel);
  servoRight.attach(rightwheel);
}

//Defining getDistance function
bool Robot::isobstacle() {
  long duration;
  int distance;
  pinMode(ultrasonic,OUTPUT);
  digitalWrite(ultrasonic, LOW); // set the pin to low
  delayMicroseconds(2); // wait for 2 microseconds
  digitalWrite(ultrasonic, HIGH); // set the pin to high to trigger the sensor
  delayMicroseconds(5); // wait for 10 microseconds
  digitalWrite(ultrasonic, LOW); // set the pin to low again to switch to echo mode

  pinMode(ultrasonic,INPUT);
  duration = pulseIn(ultrasonic, HIGH); // measure the duration of the sound wave travel
  distance = duration * 0.034 / 2; // calculate the distance in cm
  
  Serial.print("Obstacles in ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance<15)
    return true;
  else
    return false;
}

//Defining drive function
void Robot::drive(char i) {
  switch(i){
  // f, b, l, r, s means forward, backward, left, right, and stop
    case 'f':servoLeft.write(1550);servoRight.write(1450);Serial.println("f");break;
    case 'b':servoLeft.write(1450);servoRight.write(1550);break;
    case 'l':servoLeft.write(1450);servoRight.write(1450);break;
    case 'r':servoLeft.write(1550);servoRight.write(1550);break;
    case 's':servoLeft.write(1500);servoRight.write(1500);delay(20);break;
    default:Serial.println("Unclear command for motors");break;
  }
}

//run this method continuesly to follow the line until the robot meets an intersection
bool Robot::linefollowing(){
  int SL = digitalRead(IR_ML);
  int SR = digitalRead(IR_MR);
  if (SL == white && SR == white) {
    //forward
    drive('f');Serial.println("Line is Centered");return true;
  }
  else if (SL == black && SR== white) {
    //turn left
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

//Defining lcd display function
void Robot::display() {
  
}

//for test purpose
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

    //1st step: follow the line and enter the intersection
    localfinish=false;
    while(!localfinish){
      if(!rob.linefollowing()){     //if meet intersection
        rob.drive('f');delay(500); 
        rob.drive('r');delay(1000); //turn right
        c_intersection++; //record  the intersections have been passed
        localfinish=true;
      }
    }

    //2nd step: obstacle detection
    localfinish=false;
    int c_itsc=0;
    bool isintersection=false;
    bool pre=false;
    unsigned long enteritsc=0;
    unsigned long startTime=0;
    unsigned long endTime=0;
    while(!localfinish){
      //move the robot
      isintersection=!rob.linefollowing();
      if(isintersection && c_itsc==0) { //if meet intersection
        rob.drive('f');delay(500); 
        rob.drive('r');delay(2300); //turn 180
        c_itsc+=1;pre=false;
      }
      else if(isintersection && c_itsc==2){
        rob.drive('f');delay(500);
        rob.drive('l');delay(2300);//turn 180
        c_itsc+=1;parkidx+=1;
      }
      else if(isintersection && c_itsc==1){
        rob.drive('f');delay(1000);//pass the intersection
        c_itsc+=1;pre=false;parkidx+=1;
      }
      else if(isintersection && c_itsc==3){
        rob.drive('f');delay(500);
        rob.drive('l');delay(1000);//turn left
        localfinish=true;
      }

      //call ultrasonic function to detect obstacles
      if(!isintersection && c_itsc==1){
        if(pre==false && rob.isobstacle()==true){
          startTime=millis();parkinglot[parkidx]=1;pre=true;
        }
        if(pre==true && rob.isobstacle()==false){
          endTime=millis();pre=false;
        }
      }
      if(!isintersection && c_itsc==2){
        if(pre==false && rob.isobstacle()==true){
          startTime=millis();parkinglot[parkidx]=1;pre=true;
        }
        if(pre==true && rob.isobstacle()==false){
          endTime=millis();pre=false;
        }
      }
    }
      
    //3rd step: park
    localfinish=false;
    while(!localfinish){
      //check if it's the last two praking spots
      if(parkidx==8 && parkinglot[6]==1 && parkinglot[7]==0){
        //display no parking spot is found and stop
        rob.drive('s');
      }
      if(!rob.linefollowing()==0){
        if(parkinglot[parkidx-2]==0){
          rob.drive('f');delay(500);
          rob.drive('r');delay(1000);//turn right
          while(rob.linefollowing()){}
          finish=true;localfinish=true;
        }
        else if(parkinglot[parkidx-1]==0){
          rob.drive('f');delay(500);
          rob.drive('l');delay(1000);//turn left
          while(rob.linefollowing()){}
          finish=true;localfinish=true;
        }
        else{
          rob.drive('f');delay(1000);
          localfinish=true; //not globally finished yet
        }
      }
    }
      
  }
}
