//Accelerometer + 8x8 NeoPixel LEDs
//Light Up LEDs (2x2) on 8x8 grid based on orientation of Board
/*
  X Range: 300 to 460
  Y Range: 300 to 460
  Z Range: 300 to 460

*/
//Calibrate Accelerometer based on Min/Max values at different tilts.
//Accel ADC values are a function of VDD and other variables and may change slightly over time
#define X_MIN 350
#define X_MAX 440
#define Y_MIN 350
#define Y_MAX 420
#define Z_MIN 300
#define Z_MAX 460

#include <Adafruit_NeoPixel.h>

#define PIN 9      //DIN Pin on Arduino

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

//declare Pins
const int x_pin = A2;
const int y_pin = A1;
const int z_pin = A0;

int x_val, y_val, z_val;
int row_prev, col_prev; //store location of previous LEDs

int DIN = 9;    //Data Input for Neopixel

void setup() {
//  Serial.begin(9600);
  //intialize 8x8 Grid
  strip.begin();    //initial pin as output for data transmission
  strip.show();
  
  strip.setBrightness(50);    //adjust as necessary
  
}//end setup

void loop() {
  //sample accelerometer values at beginning of every loop
  x_val = analogRead(x_pin);
  y_val = analogRead(y_pin);
  z_val = analogRead(z_pin);
  
  int row, col;    //store row and column index of grid

/*
  //display to serial monitor
  Serial.print("X = ");
  Serial.print(x_val);  
  Serial.print(" Y = ");
  Serial.print(y_val);    
  Serial.print(" Z = ");
  Serial.println(z_val);   
*/
  //Acclerometer algorithm to control NeoPixel
  if (z_val < 350) {    //turn central squares/ball on when  board gets flipped
     //calculate row and column position based on accelerometer values
     col = parse_range(x_val, X_MIN, X_MAX);    //convert Accel value to column
     row = parse_range(y_val, Y_MIN, Y_MAX);    //find row pixel
     
     if (col != col_prev || row != row_prev) {     //pixels changed
  
         //clear previous pixels (row_prev, col_prev)
         strip.setPixelColor(matrix(row_prev,col_prev), 0);
         strip.setPixelColor(matrix(row_prev,col_prev+1), 0);
         strip.setPixelColor(matrix(row_prev+1,col_prev), 0);
         strip.setPixelColor(matrix(row_prev+1,col_prev+1), 0);   
         strip.show();

         //set Pixel Square based on new row, col values
         strip.setPixelColor(matrix(row,col), Wheel(100));
         strip.setPixelColor(matrix(row,col+1), Wheel(100));
         strip.setPixelColor(matrix(row+1,col), Wheel(100));
         strip.setPixelColor(matrix(row+1,col+1), Wheel(100));   
         strip.show();
      /*
         Serial.print("col = ");
         Serial.println(col);
         Serial.print("row = ");
         Serial.println(row);
      */

      /*   
         Serial.println("col != col_prev or row != row_prev");
         Serial.print("col = ");
         Serial.print(col);
         Serial.print("\t col_prev = ");
         Serial.print(col_prev);
         delay(1000);  */
         
     }//end if not equal

    //store prev row, col position
    col_prev = col;
    row_prev = row;
     
  }
  else {    //turn all LEDs off
     for (int i = 0; i < strip.numPixels(); i++) {
       strip.setPixelColor(i, 0);        
     }//end for
     strip.show();
     /*
     strip.setPixelColor(matrix(4,4), 0);
     strip.setPixelColor(matrix(4,5), 0);
     strip.setPixelColor(matrix(5,4), 0);
     strip.setPixelColor(matrix(5,5), 0);
     strip.show();
     */
  }
  
  delay(100);
}//end loop
//Math/Intermediate Functions (Miran)
//row/col start from 1 and go to 8 for an 8x8 grid
int matrix(int row, int col) {
    return (row-1)*8 + col - 1;
}

int parse_range(int val, int MIN, int MAX) {
   //returns an integer between 1 and 7 corresponding to X_range 
   int delta = (MAX - MIN)/7;    //how many instructs to run??? Should we hardcode instead?
   if (val <= MIN + delta) {
       return 7;
   }
   else if (val <= MIN+2*delta) {
      return 6; 
   }
   else if (val <= MIN+3*delta) {
      return 5; 
   }
   else if (val <= MIN+4*delta) {
      return 4; 
   }
   else if (val <= MIN+5*delta) {
      return 3; 
   }
   else if (val <= MIN+6*delta) {
      return 2;
   }
   else {
      return 1; 
   }
}

//*******************************************************************
//NeoPixel Functions
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
