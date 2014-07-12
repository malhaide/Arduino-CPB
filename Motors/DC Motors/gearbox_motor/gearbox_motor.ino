//Program to Run Robot Gearmotor
//Miran (4/16/14)

#include <PWM.h>

//initialize variable pins
  int inA = 7;  //digital output
  int inB = 8;  //digital output
  int pwm_pin = 10;    //pwm output
  int enA = 2;  //dig out
  int enB = 4;  //dig out
  
  //feedback variables
  float CS = 0;   //current sense feedback value
  int speed_duty = 0;    //duty speed
    
  //set PWM frequency??
  bool success = SetPinFrequency(pwm_pin, 2);    //sets pwm freq = 31250/2 = 15625 Hz. Note: This may affect delay(), and other pins

void setup(){
  //initialize dig pins (set direction)

  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(pwm_pin, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
}
void loop(){
  
  //ccw rotation: inA = 0; inB = 1;
  //cw rotation: inA = 1; inB = 0;
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);  
  
  //set motor speed (PWM)
  speed_duty = 255;    //set motor speed (b/t 0 and 255)
  analogWrite(pwm_pin, speed_duty);    //duty speed determines duty cyle/speed of motor
  
}
