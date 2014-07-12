//Play Audio Tones (1-5) using 5 different (Analog) inputs/switches
//Written by Miran (6/18/14)
//Volume varies depending on how hard you press on the cup

#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include <Bounce2.h> 

//Macro for Keys
#define A   A0    //analog pins
#define B   A1
#define C   A2
#define D   A3
#define E   A4

int count;  //increment when keys are pressed in order. if A,B,C,D,E (in that order) then count == 5 (play jingle)

#define PRESSURE_THRESHOLD 250    //range: 0 (least sensitive/more pressure) to 1023 (most sensitive/least pressure)

/**
 * \brief Object instancing the SdFat library.
 *
 * principal object for handling all SdCard functions.
 */
SdFat sd;
/**
 * \brief Object instancing the SFEMP3Shield library.
 *
 * principal object for handling all the attributes, members and functions for the library.
 */
SFEMP3Shield MP3player;

//------------------------------------------------------------------------------
/**
 * \brief Setup the Arduino Chip's feature for our use.
 *
 * After Arduino's kernel has booted initialize basic features for this
 * application, such as Serial port and MP3player objects with .begin.
 */
void setup() {
  Serial.begin(9600);
  Serial.println("Serial Connection Established");
//initialize analog pins as inputs with pull-up resistors activated  
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(C, INPUT_PULLUP);
  pinMode(D, INPUT_PULLUP);
  pinMode(E, INPUT_PULLUP);
//  pinMode(F, INPUT_PULLUP);
  
  if(!sd.begin(9, SPI_HALF_SPEED)) sd.initErrorHalt();
  if (!sd.chdir("/")) sd.errorHalt("sd.chdir");

  MP3player.begin();
  MP3player.setVolume(10,10);    //sets volume?
  
} //end setup

void loop() {    
  //store ADC value of button state (between 0 and 1023)
  int valA = analogRead(A);
  int valB = analogRead(B);
  int valC = analogRead(C);
  int valD = analogRead(D);
  int valE = analogRead(E);    
   
  if (valA < PRESSURE_THRESHOLD) {
    Serial.println("A was pressed");
    MP3player.playTrack(1);  //delete when done
    delay(500);
    MP3player.stopTrack();
  
    count = 1;
  }
  else if (valB < PRESSURE_THRESHOLD) {
    Serial.println("B was pressed");
    MP3player.playTrack(2);
    delay(500);
    MP3player.stopTrack();
  
    if (count == 1) {  //A was just played
      count++;    //count = 2
    }
    else {
      count = 0;  //reset back to 0
    }  
  }
  else if (valC < PRESSURE_THRESHOLD) {
    Serial.println("C was pressed");
    MP3player.playTrack(3);
    delay(500);
    MP3player.stopTrack();
    
    if (count == 2) {  //if A, B played
       count++;  // count = 3
    }
    else {
      count = 0;  //reset counter
    }  
  }
  else if (valD < PRESSURE_THRESHOLD) {
    Serial.println("D was pressed");
    MP3player.playTrack(4);
    delay(500);
    MP3player.stopTrack();
    
    if (count == 3) {
      count++;    //count = 4
    }
    else {
      count = 0;
    }
  }
  else if (valE < PRESSURE_THRESHOLD) {
    Serial.println("E was pressed");
    MP3player.playTrack(5);
    delay(500);
    MP3player.stopTrack();
    
    if (count == 4) { //A,B,C,D
      count++;  //count = 5
    }
    else {
      count = 0;
    }  
  }
  
  //if A,B,C,D, then E were played (in that order) then count = 5 so play final jingle
  if  (count == 5) {
     Serial.println("Final Jingle play"); 
     MP3player.playTrack(6);
     delay(2000);
     MP3player.stopTrack();
     
     //reset counter
     count = 0;
  }
  
  /*
  Serial.println("Count = ");
  Serial.println(count);
  delay(1000);
  */
  
  //print button states. Diagnostic code that can be deleted
  Serial.println(valA);
  Serial.println(valB);
  Serial.println(valC);
  Serial.println(valD);
  Serial.println(valE);
  Serial.println(count);
  
  //slow the loop down a bit to prevent button debouncing
 // delay(1000);

}//end loop

