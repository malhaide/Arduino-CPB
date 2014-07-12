//Simplest Code to playback audio tunes on MP3 Shield
//Selected Code from FilePlayer.ino
//Written by Miran
//Process: Add (wired) Serial comm first, then add bluetooth comm to trigger audio files
/* Do not include
  -Error Codes
  -help function
  -skip, next track, etc. functions

*/

#include <SPI.h>
#include <SdFat.h>
#include <SFEMP3Shield.h>
#include <SoftwareSerial.h>

//declare variables/objects
SdFat sd;
SFEMP3Shield MP3player;
int16_t last_ms_char; // milliseconds of last recieved character from Serial port.
int8_t buffer_pos;  //next position to receive character from Serial port.


char buffer[6];    //0-35K+null

void setup()
{
  uint8_t result;  //result code from some fn as to be testing at later time.
  
  //USB Serial Communication. Remove/Change later
  Serial.begin(9600);    //lowered the baudrate
  //sanity check
  Serial.println("Established Serial Communication!");
  
 //initialize the SdCard.
 if (!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
 // depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
 if(!sd.chdir("/")) sd.errorHalt("sd.chdir");

  //Initialize the MP3 Player Shield
  result = MP3player.begin();
  
  buffer_pos = 0;  //start the command string at zero length.
  
}  //end setup

void loop()
{
  
  char inByte;
  if (Serial.available() > 0) {
    inByte = Serial.read();
    if ((0x20 <= inByte) && (inByte <= 0x126)) { // strip off non-ASCII, such as CR or LF
      if (isDigit(inByte)) { // macro for ((inByte >= '0') && (inByte <= '9'))
        // else if it is a number, add it to the string
        buffer[buffer_pos++] = inByte;
      } else {
        // input char is a letter command
        buffer_pos = 0;
        parse_menu(inByte);
      }
      buffer[buffer_pos] = 0; // update end of line
      last_ms_char = millis(); // stroke the inter character timeout.
    }
  } else if ((millis() - last_ms_char) > 500 && ( buffer_pos > 0 )) {
    // ICT expired and have something
    if (buffer_pos == 1) {
      // look for single byte (non-number) menu commands
      parse_menu(buffer[buffer_pos - 1]);

    } else if (buffer_pos > 5) {
      // dump if entered command is greater then uint16_t
      Serial.println(F("Ignored, Number is Too Big!"));

    } else {
      // otherwise its a number, scan through files looking for matching index.
      int16_t fn_index = atoi(buffer);
      SdFile file;
      char filename[13];
      sd.chdir("/",true);
      uint16_t count = 1;
      while (file.openNext(sd.vwd(),O_READ))
      {
        file.getFilename(filename);
        if ( isFnMusic(filename) ) {

          if (count == fn_index) {
  /*          Serial.print(F("Index "));
            SerialPrintPaddedNumber(count, 5 );
            Serial.print(F(": "));
            Serial.println(filename);
            Serial.print(F("Playing filename: "));
            Serial.println(filename);    */
            int8_t result = MP3player.playMP3(filename);
            //check result, see readme for error codes.
            if(result != 0) {
              Serial.print(F("Error code: "));
              Serial.print(result);
              Serial.println(F(" when trying to play track"));
            }
            char title[30]; // buffer to contain the extract the Title from the current filehandles
            char artist[30]; // buffer to contain the extract the artist name from the current filehandles
            char album[30]; // buffer to contain the extract the album name from the current filehandles
            MP3player.trackTitle((char*)&title);
            MP3player.trackArtist((char*)&artist);
            MP3player.trackAlbum((char*)&album);

            //print out the arrays of track information
 /*           Serial.write((byte*)&title, 30);
            Serial.println();
            Serial.print(F("by:  "));
            Serial.write((byte*)&artist, 30);
            Serial.println();
            Serial.print(F("Album:  "));
            Serial.write((byte*)&album, 30);
            Serial.println();
            break;    */
          }
          count++;
        }
        file.close();
      }

    }

    //reset buffer to start over
    buffer_pos = 0;
    buffer[buffer_pos] = 0; // delimit
  }

  delay(100);  
  
  
  
}//end loop
    
//------------------------------------------------------------------------------
/**
 * \brief Decode the Menu.
 *
 * Parses through the characters of the users input, executing corresponding
 * MP3player library functions and features then displaying a brief menu and
 * prompting for next input command.
 */
 void parse_menu(byte key_command) {
   uint8_t result;  //result code from some function as to be tested at later time.
   
  Serial.print(F("Received command: "));
  Serial.write(key_command);
  Serial.println(F(" "));
   
  //if s, stop the current track
  if(key_command == 's') {
    Serial.println(F("Stopping"));
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
    Serial.print(F("Volume changed to -"));
    Serial.print(mp3_vol.byte[1]>>1, 1);
    Serial.println(F("[dB]"));
  }//end +/-
  else if(key_command == 'R') {
    MP3player.stopTrack();
    MP3player.vs_init();
    Serial.println(F("Reseting VS10xx chip"));

  }
   
   //CUTOUT: A bunch of different functions/key commands for parse
   
 }//end parse_menu
 //-----------------------------------------------------------------------------------------------------
void SerialPrintPaddedNumber(int16_t value, int8_t digits ) {
  int currentMax = 10;
  for (byte i=1; i<digits; i++){
    if (value < currentMax) {
      Serial.print("0");
    }
    currentMax *= 10;
  }
  Serial.print(value);
}
