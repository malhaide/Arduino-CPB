//Using Servo HiTec HS-5485HB
//90 degree range?
//By Miran (4/22/14)

#include <Servo.h>

Servo myservo;  //Servo object declaration

void setup()
{
  //myservo.attach(9, 100, 2000);   //assign servo to specific signal pin. min,max in usecs
  myservo.attach(9);
  
  myservo.write(90);    //set initial angle of shaft 
}

void loop()
{
  myservo.write(0);
  delay(1000);
  myservo.write(90);
}
