//Simplest (bare bones) code that can echo bluetooth code back to user
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SdFat.h>
#include <SFEMP3Shield.h>

//declare variables/objects
SdFat sd;
SFEMP3Shield MP3player;
int16_t last_ms_char; // milliseconds of last recieved character from Serial port.
int8_t buffer_pos;  //next position to receive character from Serial port.

SoftwareSerial mySerial(10,11);

String command = "";

int LED = 5;

void setup() {
  mySerial.begin(9600);
  
  //blink LED for 1 sec
  pinMode(LED, OUTPUT);
  
  uint8_t result;  //result code from some fn as to be testing at later time.

/*
 //initialize the SdCard.
 if (!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
 // depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
 if(!sd.chdir("/")) sd.errorHalt("sd.chdir");       
*/

  //Initialize the MP3 Player Shield
  result = MP3player.begin();


  //sanity check blink LED for 1 sec
  digitalWrite(LED, HIGH);
  delay(2000);
  digitalWrite(LED, LOW);
  
}//end setup

void loop() {
//  mySerial.println("please enter command: ");

  mySerial.println("Bluetooth connection established");   //does not execute

  if (mySerial.available()) {
    while (mySerial.available()) {
      command += (char)mySerial.read();  //one by one store typed text into command string
    }//end while
    
   command += 'x';  //concatenate an x to signify that this code is running correctly 
   mySerial.println(command); //executed
   command = "";  //rest command 
    
    }//end if available

 delay(1000);
 
}//end loop

//--------------------------------------------------------------------------------------------------
/**
 * \brief Decode the Menu.
 *
 * Parses through the characters of the users input, executing corresponding
 * MP3player library functions and features then displaying a brief menu and
 * prompting for next input command.
 */
 void parse_menu(byte key_command) {
   uint8_t result;  //result code from some function as to be tested at later time.
   
    mySerial.print(F("Received command: "));
    mySerial.write(key_command);
    mySerial.println(F(" "));
   
  //if s, stop the current track
  if(key_command == 's') {
    mySerial.println(F("Stopping"));
    MP3player.stopTrack();
  }
  //if 1-9, play corresponding track
  else if (key_command >= '1' && key_command <= '9')
  {
    //convert ascii numbers to real numbers
    key_command = key_command - 48;
    //tell the MP3 Shield to play a track
    result = MP3player.playTrack(key_command);    
   
   //Cut out error check... for now
   
   //Cut out Track info... for now
   
  }//if +/- to change volume
  else if ((key_command == '-') || (key_command == '+')) {
    union twobyte mp3_vol; // create key_command existing variable that can be both word and double byte of left and right.
    mp3_vol.word = MP3player.getVolume(); // returns a double uint8_t of Left and Right packed into int16_t

    if(key_command == '-') { // note dB is negative
      // assume equal balance and use byte[1] for math
      if(mp3_vol.byte[1] >= 254) { // range check
        mp3_vol.byte[1] = 254;
      } else {
        mp3_vol.byte[1] += 2; // keep it simpler with whole dB's
      }
    } else {
      if(mp3_vol.byte[1] <= 2) { // range check
        mp3_vol.byte[1] = 2;
      } else {
        mp3_vol.byte[1] -= 2;
      }
    }
    // push byte[1] into both left and right assuming equal balance.
    MP3player.setVolume(mp3_vol.byte[1], mp3_vol.byte[1]); // commit new volume
    mySerial.print(F("Volume changed to -"));
    mySerial.print(mp3_vol.byte[1]>>1, 1);
    mySerial.println(F("[dB]"));
  }//end +/-
  else if(key_command == 'R') {
    MP3player.stopTrack();
    MP3player.vs_init();
    mySerial.println(F("Reseting VS10xx chip"));

  }
   
   //CUTOUT: A bunch of different functions/key commands for parse
   
 }//end parse_menu
 //-----------------------------------------------------------------------------------------------------
void SerialPrintPaddedNumber(int16_t value, int8_t digits ) {
  int currentMax = 10;
  for (byte i=1; i<digits; i++){
    if (value < currentMax) {
      mySerial.print("0");
    }
    currentMax *= 10;
  }
  mySerial.print(value);
}
