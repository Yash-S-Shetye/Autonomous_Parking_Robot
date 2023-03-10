/* HelloWorldLcd */
const int TxPin = 12; // Can use any pin from 2 to 12
#include <SoftwareSerial.h>
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);
void setup() {
//pinMode(TxPin, OUTPUT);
//digitalWrite(TxPin, HIGH);
mySerial.begin(9600);
delay(100);
mySerial.write(12); // Clear
mySerial.write(17); // Turn backlight on
delay(5); // Required delay
/*for(int ctr=0; ctr<=12; ctr++)
{
mySerial.print(ctr);
mySerial.write(" ");
delay(500);
}*/
mySerial.print("Hello");
mySerial.write(" ");
mySerial.print("World");
}
void loop() {
}
