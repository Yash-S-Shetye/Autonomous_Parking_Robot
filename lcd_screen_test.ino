/* HelloWorldLcd */
const int TxPin = 6; // Can use any pin from 2 to 12
#include <SoftwareSerial.h>
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);
void setup() {
  pinMode(TxPin, OUTPUT);
  digitalWrite(TxPin, HIGH);
  mySerial.begin(9600);
  delay(100);
  mySerial.write(12); // Clear
  mySerial.write(17); // Turn backlight on
  delay(5); // Required delay
  mySerial.print("Hello, world..."); // First line
  mySerial.write(13); // Form feed
  mySerial.print("from Parallax!"); // Second line
  mySerial.write(212); // Quarter note
  mySerial.write(220); // A tone
  delay(3000); // Wait 3 seconds
  mySerial.write(12); // Clear
  delay(5); // Required delay
  mySerial.write(128); // Row 0, Col 0
  mySerial.print("Hello"); // First line
  mySerial.write(13); // Form feed
  mySerial.print("World...!"); // Second line
  delay(2000);
  mySerial.write(18); // Turn backlight off
}
void loop() { }
