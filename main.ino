#define trigpin 9
#define echopin 10
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

}

void loop(){

}
