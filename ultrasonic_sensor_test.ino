const int SigPin = 8;
float invcmCosnt = (2*1000000)/(100*344.8); //cmDist=rawTime/invcmCosnt
float invinCosnt = invcmCosnt*2.54; //inDist=rawTime/invinCosnt
void setup() {
Serial.begin(9600);
}
void loop() {
float rawTime, inDist, inDist1, cmDist, cmDist1; //declare variables
/* Ping))) produces chirp when a HIGH pulse of 2us (min) or longer duration (5us typical) is
applied to Sig pin. To have a clarn HIGH pulse, give a low and then high */
pinMode(SigPin, OUTPUT);
digitalWrite(SigPin, LOW);
delayMicroseconds(2);
digitalWrite(SigPin, HIGH);
delayMicroseconds(5);
digitalWrite(SigPin, LOW);
/* Now same Sign pin is to be used to monitor if the return echo has been received. Essentially,
Sig pin remains HIGH until a return echo is received and at that time it goes LOW. So measure
the time duration for HIGH at the Sig pin */
pinMode(SigPin, INPUT);
rawTime = pulseIn(SigPin, HIGH); //measured in u-seconds
cmDist = rawTime/invcmCosnt;
Serial.print(cmDist);
Serial.println("cm, ");
delay(1000);
}
