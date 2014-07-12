//Servo Motor Control Test
//By Miran / 4/15/14

#include <Servo.h>

Servo myservo;  //Servo object declaration

void setup()
{
  //myservo.attach(9, 100, 2000);   //assign servo to specific signal pin. min,max in usecs
  myservo.attach(9);
  
  myservo.write(0);    //set initial angle of shaft 
}

void loop()
{
  delay(2000);
  myservo.write(0);
  delay(2000);
  myservo.write(90);
  delay(1000);
  myservo.write(180);
}
