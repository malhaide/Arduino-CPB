//Using Software Serial library (pins 10, 11)
//


#include <SoftwareSerial.h>
char receivedChar;
int  LED = 5; // LED on pin 13
SoftwareSerial mySerial(10, 11); // RX, TX

//RX on Bluetooth to TCX on Arduino through a voltage divider 50ohm from arduino and 100ohm to ground. This is so we can drop the the voltage down to 3.3v (roughly)
// Use blueterm on android to get messages
int sensorPin = A0;
void setup()
{
  // Open serial communications and wait for port to open:
  pinMode(LED, OUTPUT);
  mySerial.begin(9600);
  mySerial.println("Welcome to the wonderful world of bluetooth communication");
  delay(1000);
  mySerial.println("Sending a '1' will turn on the LED, Sending a '0' will turn off the LED");
  delay(1000);
  mySerial.println("a '3' will flash the LED and a '4' will kick out a lot of data from the LDR");
}

void loop() // run over and over
{

  while (!mySerial.available());   // stay here so long as COM port is empty
  receivedChar = mySerial.read();
  if (receivedChar == '1') {
    digitalWrite(LED, HIGH);
  }// if it's a 1 turn LED on
  if (receivedChar == '2') {
    digitalWrite(LED, LOW);
  } // if it's a 2 turn LED off
  if (receivedChar == '3') {
    for (int i = 0; i < 30; i++) {
      digitalWrite(LED, HIGH);
      delay(20);
      digitalWrite(LED, LOW);
      delay(20);
    }
  } // if it is a 3 flash the LED
  if (receivedChar == '4') {
    for (int i = 0; i < 100; i++) {
      delay(20);
      int sensorValue = analogRead(sensorPin);
      float voltage = sensorValue * (5.0 / 1023.0);
      mySerial.println(voltage);
    }
  } // if it is a 4 print out lots of sensor data

}

