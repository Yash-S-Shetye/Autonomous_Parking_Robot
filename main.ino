#define trigpin 9
#define echopin 10
#define leftwheel 5
#define rightwheel 6

class Robot {
  private:
  long duration;
  int distance;
  
  public:
  void getDistance();
};

void setup(){
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  Serial.begin(9600);
}

void loop(){

}
