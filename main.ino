#define trigpin 9
#define echopin 10
#define leftwheel 5
#define rightwheel 6
long duration;
int distance;

double getdistance(){
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(LOW);
  duration=pulseIn(echopin,HIGH);
  distance=duration*0.034/2;
  Serial.print('Distance=');
  Serial.println(distance);
  return distance;
}
void setup(){
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  Serial.begin(9600);
}

void loop(){

}
