//*******************************************************************************
//Trigger 3 audio tones on Audio recorder via Bluetooth HC-06 module
//if you send 'a' then trigger ch1
//if you send 'b' then trigger ch2
//if you send 'c' then trigger ch3
//******************************************************************************
//Written by Miran (5/7/14)
//SoftwareSerial connection to Tx/Rx from HC-06 directly
//using software-defined serial connection, mySerial, to Tx and Rx from BT module
#include <SoftwareSerial.h>

int LED = 2;  //LED set-up on (digital) pin 2
int CH1 = 7, CH2 = 6, CH3 = 5;  //specific to connections


SoftwareSerial mySerial(10, 11); // RX, TX (from arduino POV)
String command = ""; // Stores response of bluetooth device
                                     // which simply allows \n between each
                                     // response.
void setup() 
{
   //setup pin 2 as output for LED
   pinMode(LED, OUTPUT); 
   pinMode(CH1, OUTPUT);
   pinMode(CH2, OUTPUT);
   pinMode(CH3, OUTPUT);
   
  // Open serial communications and wait for port to open:
   Serial.begin(9600);   
   Serial.println("Type AT commands!");
   // SoftwareSerial "com port" data rate. JY-MCU v1.03 defaults to 9600.
   mySerial.begin(9600);
   
  //sanity check blink LED for 1 sec
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  
  //default ch1-3 to be high
  digitalWrite(CH1, HIGH);  //default b/c ch's are active low
  digitalWrite(CH2, HIGH);
  digitalWrite(CH3, HIGH);
}

void loop()
{
   // Read device output if available.
   if (mySerial.available()) {
     while(mySerial.available()) { // While there is more to be read, keep reading.
         command += (char)mySerial.read();    //load up entire serial command into string
       
          //code to trigger tones
          if (command == "a") {
             //turn on ch1 for 300 ms
             digitalWrite(CH1, LOW);
             delay(500);
             digitalWrite(CH1, HIGH);
             command = 0;    //reset command variable
             }//end if
          else if (command == "b") {
             //turn on ch1 for 300 ms
             digitalWrite(CH2, LOW);
             delay(500);
             digitalWrite(CH2, HIGH);
             command = 0;          
             }
          else if (command == "c") {
             //turn on ch1 for 300 ms
             digitalWrite(CH3, LOW);
             delay(500);
             digitalWrite(CH3, HIGH);
             command = 0;    //reset command variable
             }//end if 
     
     }//end wile serial available
     Serial.println(command);
     command = ""; // No repeats
   }

   // Read user input if available.
   if (Serial.available()){
       delay(10); // The DELAY!
       mySerial.write(Serial.read());
   }
}// END loop()
