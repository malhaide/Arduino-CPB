//turn LED on for 1 sec if you receive an 'A'

#include <SoftwareSerial.h>

char receivedKey;  //store keystroke

int LED = 5;  //digital pin 5
int x =0;

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);  //set baud rate
  Serial.println("Sanity Check");
 
}//end setup


void loop()
{
  while (Serial.available())    //while serial commands hit
  {
    Serial.println("Someone is typing");
    x = Serial.available();
    Serial.print("Serial.available is ");
    Serial.println(x);
    
    //store inputed char received
    receivedKey = Serial.read();
    
    //echo typed key back to serial Monitor
    Serial.print("I received: ");
    Serial.println(receivedKey, DEC);
    if (receivedKey == 'a')
        Serial.print("I received an A");
    
    //turn LED on for 1 sec if an 'a' is received
    if (receivedKey == 'a')  {    
        digitalWrite(LED, HIGH);  //turn LED on
        delay(1000);
        digitalWrite(LED, LOW);  //turn LED off
        receivedKey = 0;  //reset pin
    }    
    delay(1000);
  }//end while available

    
}//end loop

