#include <Servo.h>
#include <SoftwareSerial.h>
#define black 1
#define white 0
#define obsdistance 20
#define nighty 1000
#define oneeighty 2000

bool finish=false;                      //flag variable inidicates if the job is done
bool localfinish=false;
int parkinglot[8]={0,0,0,0,0,0,0,0};    //this arry is used to record the state of parking lot:
                                        //0-availavle, 1-occupied and cannot park, 2--occupied but can park
int parkidx=0;                          //indicates which parking lot the robot is going trough
int obstacles_no=0;                     //count how many obstacles are detected
int c_tw=0;                             //count how many two-wheel vehicles are detected

//Create a robot class containing all the functions will be used
class Robot {
  private:
  // Defining required variables: pin configuration
  const int leftwheel=2;
  const int rightwheel=3;
  const int ultrasonic=11;
  const int TxPin = 12;
  const int IR_ML=4;
  const int IR_MR=8;
  const int led=7;
  Servo servoLeft, servoRight;
  SoftwareSerial mySerial = SoftwareSerial(255, TxPin);
  
  
  public:
  //Declaring all the required functions
  void INIT();
  bool isobstacle();
  void drive(char i);
  void lcd_display(char disp);
  bool linefollowing();
  void test();
};

//Initialization: initialize the motors and lcd
void Robot::INIT(){
  servoLeft.attach(leftwheel);
  servoRight.attach(rightwheel);
  mySerial.begin(9600);
  delay(100);
  mySerial.write(12);       // Clear
  mySerial.write(17);       // Turn backlight on
  delay(5);                 // Required delay
  mySerial.print("Initialized!!!");delay(2000);
  pinMode(led,OUTPUT);
}

//Defining getDistance function
bool Robot::isobstacle() {
  long duration;
  int distance;
  pinMode(ultrasonic,OUTPUT);
  digitalWrite(ultrasonic, LOW);    // set the pin to low
  delayMicroseconds(2);             // wait for 2 microseconds
  digitalWrite(ultrasonic, HIGH);   // set the pin to high to trigger the sensor
  delayMicroseconds(10);            // wait for 10 microseconds
  digitalWrite(ultrasonic, LOW);    // set the pin to low again to switch to echo mode

  pinMode(ultrasonic,INPUT);
  duration = pulseIn(ultrasonic, HIGH);   // measure the duration of the sound wave travel
  distance = duration * 0.034 / 2;        // calculate the distance in cm
  
  
  if (distance<obsdistance){
    // blink the led if obstacle is detected
    digitalWrite(led,HIGH);delay(50);
    digitalWrite(led,LOW);delay(50);
    return true;}
  else{
    //digitalWrite(led,LOW);delay(10);
    return false;}
}

//Defining drive function
void Robot::drive(char i) {
  switch(i){
  // f, b, l, r, s means forward, backward, left, right, and stop
    case 'f':servoLeft.write(1550);servoRight.write(1440);delay(20);break;
    case 'b':servoLeft.write(1450);servoRight.write(1550);delay(20);break;
    case 'l':servoLeft.write(1450);servoRight.write(1450);delay(20);break;
    case 'r':servoLeft.write(1550);servoRight.write(1550);delay(20);break;
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
    drive('f');return true;
  }
  else if (SL == black && SR== white) {
    //turn left
    drive('l');return true;
  }
  else if (SL == white &&  SR == black) {
    // Turn right
    drive('r');return true;
  }
  else {
    // Stop if theres an intersection
    drive('s');return false;
  }
}

//Defining lcd display function
void Robot::lcd_display(char disp) {
  mySerial.write(12); // Clear
  mySerial.write(17); // turn on the backlight
  delay(5); // Required delay
  
  switch(disp) {
    case 'i': mySerial.print("Intersection");mySerial.write(13);mySerial.print("Detected");delay(500);mySerial.write(12);break;           // i - Intersection detected
    case 'p': mySerial.print("Parked");mySerial.write(13);mySerial.print("Successfully !!");delay(3000);mySerial.write(12);break;         // p - parked successfully
    case 's': mySerial.print("Occupied Spaces");mySerial.write(13);mySerial.print(obstacles_no);delay(3000);mySerial.write(12);break;     // s - Number of occupied spaces
    case 'f': mySerial.print("Four Wheelers");mySerial.write(13);mySerial.print(obstacles_no-c_tw);delay(3000);mySerial.write(12);break;  // f - Number of occupied spaces
    case 't': mySerial.print("Two Wheelers");mySerial.write(13);mySerial.print(c_tw);delay(3000);mySerial.write(12);break;                // s - Number of occupied spaces
    default:Serial.println("Unclear command for display");break;
  }
}

//for test purpose
void Robot::test(){
  servoLeft.write(1500);servoRight.write(1500);
}

//create robot object as a global variable
Robot rob;

void setup() {
  //initialize objects of Robot class
  Serial.begin(9600);
  rob.INIT();
}

// in the loop function, do the task by calling methods of class
void loop() {
  if(!finish){  //gloabal check flag, will set to be true when finish parking

    //phase 1: follow the line and go to the next intersection
    localfinish=false;
    while(!localfinish){
      if(!rob.linefollowing()){                 //if meet intersection
        rob.lcd_display('i');                   //display on lcd 
        rob.drive('f');delay(500);              //500 small delay to move to the center of the intersection, same purpose in the rest of the use
        rob.drive('r');delay(nighty);           //make a right turn
        localfinish=true;                       //jump to the next phase
      }
    }

    //phase 2: obstacle detection
    //declare some variables being used in this phase
    localfinish=false;
    int c_itsc=0;
    bool isintersection=false;
    unsigned long tic1, toc1, tic2, toc2, tic_size1, toc_size1, tic_size2, toc_size2;
    while(!localfinish){
      isintersection=!rob.linefollowing();    //go to the next intersection
      if(isintersection && c_itsc==0) {       //executed if the robot meets an intersection. c_itsc indicates which intersection it is.
        rob.drive('f');delay(500); 
        rob.drive('r');delay(oneeighty);      //turn 180 degrees
        tic1=millis();                        //record the time when set off from the right end of the road
        c_itsc++;
      }
      else if(isintersection && c_itsc==2){
        rob.drive('f');delay(500);
        rob.drive('r');delay(oneeighty);      //turn 180 degrees
        c_itsc++;parkidx++;
      }
      else if(isintersection && c_itsc==1){
        rob.drive('f');delay(1000);           //pass the intersection
        c_itsc++;parkidx++;tic2=millis();     //record the time when the robot pass the center of the map
      }
      else if(isintersection && c_itsc==3){
        rob.drive('f');delay(500);
        rob.drive('l');delay(nighty);         //turn left and go back to the center, ready to move to the next intersection
        localfinish=true;
      }

      //call ultrasonic function to detect obstacles while the ultrasonic sensor is towards to the parking lot and no obstacle has been detected yet
      if(!isintersection && c_itsc==1 && parkinglot[parkidx]==0){
        bool isobj=rob.isobstacle();
        if(isobj==true){
          //when we first find an obstacle
          obstacles_no++;              
          tic_size1=millis();                                           //record the time when we first find the obstacle
          while(rob.isobstacle()){if(!rob.linefollowing())break;}       //moving on while the obstacle is there
          toc_size1=millis();                                           //record the time when the obstacle ends
          if(toc_size1-tic1<3000){                                      //if the obstacle ends out of the T-section
            parkinglot[parkidx]=2;c_tw++;                               //we can park here, and it is a bonus parking case
          }
          else{                                                         //if the obstacle ends out of the T-section
            parkinglot[parkidx]=1;                                      //we cannot park
            if(toc_size1-tic_size1<1500){                               //if the obstacle is less than 9 cm (roughly)
              c_tw++;}                                                  //count it as a two-wheel vehicle
          }
        }
      }
      
      //this is roughly the same as the code above but it is for the other side of the map
      if(!isintersection && c_itsc==2 && parkinglot[parkidx]==0){
        bool isobj=rob.isobstacle();
        if(isobj==true){
          obstacles_no++;
          toc2=millis();                                                //record the time when we first find the obstacle
          if(toc2-tic2>2500){parkinglot[parkidx]=2;c_tw++;}             //if it is out of the T-section, then its a bonus parking case
          else{                                                         //if it is in the T-section
            tic_size2=millis();
            while(rob.isobstacle()){if(!rob.linefollowing()){break;}}
            toc_size2=millis(); 
            if(toc_size2-tic_size2<1500)c_tw++;                         //determine it is a two-wheel or four-wheel vehicle
            parkinglot[parkidx]=1;                                      //the robot cannot park here
          }
        }
      }
    }
      
    //3rd step: park
    localfinish=false;
    while(!localfinish){
      //check if it is the end of the map
      if(parkidx==8 && parkinglot[6]==1 && parkinglot[7]==1{
        //display no parking spot is found and stop
        rob.drive('s');finish=true;break;
      }
      if(!rob.linefollowing()){                                       //if meets the next intersection
        rob.lcd_display('i');
        if(parkinglot[parkidx-2]==0||parkinglot[parkidx-2]==2){       //check parkinglot arry to see if the parking lot on the right is availavble
          rob.drive('f');delay(500);
          rob.drive('r');delay(nighty);                               //turn right
          while(rob.linefollowing()){};
          rob.drive('s');delay(500);                                  //reach the end of the T-section and stop
          rob.lcd_display('p');                                       //display the counting for occupied parking lot, 2-wheel and 4-wheel vehicles
          rob.lcd_display('s');
          rob.lcd_display('f');
          rob.lcd_display('t');
          finish=true;localfinish=true;                               //end the program
        }
        else if(parkinglot[parkidx-1]==0||parkinglot[parkidx-1]==2){  //check parkinglot arry to see if the parking lot on the left is available
          rob.drive('f');delay(500);
          rob.drive('l');delay(nighty);                               //turn left
          while(rob.linefollowing()){};
          rob.drive('s');delay(500);
          rob.lcd_display('p');
          rob.lcd_display('s');
          rob.lcd_display('f');
          rob.lcd_display('t');
          finish=true;localfinish=true; 
        }
        else{                                                         //if no parking lot is available in this section
          rob.drive('f');delay(1000);                                 //move forward
          localfinish=true;                                           //not globally finished yet, go to the next intersection
        }
      }
    }
  }
}
