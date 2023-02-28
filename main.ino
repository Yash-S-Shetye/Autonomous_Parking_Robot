#define trigpin 9
#define echopin 10
#define leftwheel 5
#define rightwheel 6
long duration;
int distance;

void setup(){
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  Serial.begin(9600);
}

void loop(){

}
