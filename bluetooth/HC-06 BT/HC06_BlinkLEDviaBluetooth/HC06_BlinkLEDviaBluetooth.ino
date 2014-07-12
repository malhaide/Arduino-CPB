//Blink an LED on Arduino Board remotely from Bluetooth Serial Monitor
//modified from linvor_sample_code
//if you send 'a' then turn led on
//if you send 'b' then turn led off
//SoftwareSerial connection to Tx/Rx from HC-06 directly

//using software-defined serial connection, mySerial, to Tx and Rx from BT module

#include <SoftwareSerial.h>

int LED = 2;  //LED set-up on (digital) pin 2

SoftwareSerial mySerial(10, 11); // RX, TX (from arduino POV)
String command = ""; // Stores response of bluetooth device
                                     // which simply allows \n between each
                                     // response.
void setup() 
{
   //setup pin 2 as output for LED
   pinMode(LED, OUTPUT); 
 
  // Open serial communications and wait for port to open:
   Serial.begin(9600);   
   Serial.println("Type AT commands!");
   // SoftwareSerial "com port" data rate. JY-MCU v1.03 defaults to 9600.
   mySerial.begin(9600);
   
  //sanity check blink LED for 1 sec
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
   
}

void loop()
{
   // Read device output if available.
   if (mySerial.available()) {
     while(mySerial.available()) { // While there is more to be read, keep reading.
       command += (char)mySerial.read();
       
       if (command == "a") {
       //blink LED, sanity check 
       digitalWrite(LED, HIGH);
       delay(500);
       digitalWrite(LED, LOW);
       
       //echo command back
       mySerial.write("You just entered a");    
       }//end if
     }
     Serial.println(command);
   //  mySerial.println(command);  //echo command back to serial monitor
     command = ""; // No repeats
   }

   // Read user input if available.
   if (Serial.available()){
       delay(10); // The DELAY!
       mySerial.write(Serial.read());
   }
}// END loop()
