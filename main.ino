#include <Servo.h>
#include <SoftwareSerial.h>
#define black 1
#define white 0
#define obsdistance 20
#define nighty 1000
#define oneeighty 2000

bool finish=false;
bool localfinish=false;
int c_intersection=0;
int parkinglot[8]={0,0,0,0,0,0,0,0};
int parkidx=0;
int obstacles_no=0;
int c_tw=0;

//Creating a robot class containing all the functions will be used
class Robot {
  private:
  //Defining required variables
  const int leftwheel=2;
  const int rightwheel=3;
  const int ultrasonic=11;
  const int TxPin = 12;
  const int IR_ML=4;
  const int IR_MR=8;
  const int led=7;
  Servo servoLeft, servoRight;
  
  
  public:
  void INIT();
  SoftwareSerial mySerial = SoftwareSerial(255, TxPin);
  //Declaring all the required functions
  bool isobstacle();
  void drive(char i);
  void lcd_display(char disp);
  bool linefollowing();
  void test();
};

//Initialization
void Robot::INIT(){
  servoLeft.attach(leftwheel);
  servoRight.attach(rightwheel);
  mySerial.begin(9600);
  delay(100);
  mySerial.write(12); // Clear
  mySerial.write(17); // Turn backlight on
  delay(5); // Required delay
  mySerial.print("Initialized!!!");delay(2000);
  pinMode(led,OUTPUT);
}

//Defining getDistance function
bool Robot::isobstacle() {
  long duration;
  int distance;
  pinMode(ultrasonic,OUTPUT);
  digitalWrite(ultrasonic, LOW); // set the pin to low
  delayMicroseconds(2); // wait for 2 microseconds
  digitalWrite(ultrasonic, HIGH); // set the pin to high to trigger the sensor
  delayMicroseconds(10); // wait for 10 microseconds
  digitalWrite(ultrasonic, LOW); // set the pin to low again to switch to echo mode

  pinMode(ultrasonic,INPUT);
  duration = pulseIn(ultrasonic, HIGH); // measure the duration of the sound wave travel
  distance = duration * 0.034 / 2; // calculate the distance in cm
  
  
  if (distance<obsdistance){
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
    // Stop
    drive('s');return false;
  }
}

//Defining lcd display function
void Robot::lcd_display(char disp) {
  mySerial.write(12); // Clear
  mySerial.write(17);
  delay(5); // Required delay
  
  switch(disp) {
    case 'i': mySerial.print("Intersection");mySerial.write(13);mySerial.print("Detected");delay(500);mySerial.write(12);break; // i - Intersection detected
    case 'p': mySerial.print("Parked");mySerial.write(13);mySerial.print("Successfully !!");delay(3000);mySerial.write(12);break; // p - parked successfully
    case 's': mySerial.print("Occupied Spaces");mySerial.write(13);mySerial.print(obstacles_no);delay(3000);mySerial.write(12);break; // s - Number of occupied spaces
    case 'f': mySerial.print("Four Wheelers");mySerial.write(13);mySerial.print(obstacles_no-c_tw);delay(3000);mySerial.write(12);break; // s - Number of occupied spaces
    case 't': mySerial.print("Two Wheelers");mySerial.write(13);mySerial.print(c_tw);delay(3000);mySerial.write(12);break; // s - Number of occupied spaces
    default:Serial.println("Unclear command for display");break;
  }
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
        rob.lcd_display('i');
        rob.drive('f');delay(500); 
        rob.drive('r');delay(nighty); //turn right
        c_intersection++; //record  the intersections have been passed
        localfinish=true;
      }
    }

    //2nd step: obstacle detection
    localfinish=false;
    int c_itsc=0;
    bool isintersection=false;
    unsigned long tic1, toc1, tic2, toc2, tic_size1, toc_size1, tic_size2, toc_size2;
    while(!localfinish){
      //move the robot
      isintersection=!rob.linefollowing();
      if(isintersection && c_itsc==0) { //if meet intersection
        rob.drive('f');delay(500); 
        rob.drive('r');delay(oneeighty); //turn 180
        tic1=millis();
        c_itsc++;
      }
      else if(isintersection && c_itsc==2){
        rob.drive('f');delay(500);
        rob.drive('r');delay(oneeighty);//turn 180
        c_itsc++;parkidx++;
      }
      else if(isintersection && c_itsc==1){
        rob.drive('f');delay(1000);//pass the intersection
        c_itsc++;parkidx++;tic2=millis();
      }
      else if(isintersection && c_itsc==3){
        rob.drive('f');delay(500);
        rob.drive('l');delay(nighty);//turn left
        localfinish=true;
      }

      //call ultrasonic function to detect obstacles
      if(!isintersection && c_itsc==1 && parkinglot[parkidx]==0){
        bool isobj=rob.isobstacle();
        if(isobj==true){
          obstacles_no++;
          toc1=millis();
          tic_size1=millis();
          while(rob.isobstacle()){if(!rob.linefollowing())break;}
          toc_size1=millis();
//          rob.mySerial.write(12); // Clear
//          rob.mySerial.write(17);
//          delay(5); // Required delay
//          rob.mySerial.print(toc_size1-tic1);rob.drive('s');delay(5000);
          if(toc_size1-tic1<3000){
            parkinglot[parkidx]=2;c_tw++;
          }
          else{
            parkinglot[parkidx]=1;
            if(toc_size1-tic_size1<1500){
              c_tw++;}
          }
        }
        
      }
      if(!isintersection && c_itsc==2 && parkinglot[parkidx]==0){
        bool isobj=rob.isobstacle();
        if(isobj==true){
          obstacles_no++;
          toc2=millis();
//          rob.mySerial.write(12); // Clear
//          rob.mySerial.write(17);
//          delay(5); // Required delay
//          rob.mySerial.print(toc2-tic2);rob.drive('s');delay(5000);
          if(toc2-tic2>2500){parkinglot[parkidx]=2;c_tw++;}
          else{
            tic_size2=millis();
            while(rob.isobstacle()){if(!rob.linefollowing()){break;}}
            toc_size2=millis(); 
            if(toc_size2-tic_size2<1500)c_tw++;
            parkinglot[parkidx]=1;
          }
        }
      }
    }
      
    //3rd step: park
    localfinish=false;
    while(!localfinish){
      //check if it's the last two parking spots
      if(parkidx==8 && parkinglot[6]==1 && parkinglot[7]==0){
        //display no parking spot is found and stop
        rob.drive('s');
      }
      if(!rob.linefollowing()){
        rob.lcd_display('i');
        if(parkinglot[parkidx-2]==0||parkinglot[parkidx-2]==2){
          rob.drive('f');delay(500);
          rob.drive('r');delay(nighty);//turn right
          while(rob.linefollowing()){};
          rob.drive('s');delay(500);
          rob.lcd_display('p');
          rob.lcd_display('s');
          rob.lcd_display('f');
          rob.lcd_display('t');
          finish=true;localfinish=true;
        }
        else if(parkinglot[parkidx-1]==0||parkinglot[parkidx-1]==2){
          rob.drive('f');delay(500);
          rob.drive('l');delay(nighty);//turn left
          while(rob.linefollowing()){};
          rob.drive('s');delay(500);
          rob.lcd_display('p');
          rob.lcd_display('s');
          rob.lcd_display('f');
          rob.lcd_display('t');
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
