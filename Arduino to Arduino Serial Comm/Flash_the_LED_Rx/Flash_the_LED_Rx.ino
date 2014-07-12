/*                Receiver
For more details see: http://projectsfromtech.blogspot.com/

Connect the Tx pin of this board to the Rx of the board running Flash_the_LED__Tx.ino
Connect the Grounds of the two boards

Receive an integer value over the serial and 
flashes the LED the appropriate number of times
*/

#include <LiquidCrystal.h>

// Connections:
// rs (LCD pin 4) to Arduino pin 12
// rw (LCD pin 5) to Arduino pin 11
// enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 5, 4, 3, 2
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
int backLight = 13;    // pin 13 will control the backlight

int val = 0;
const int led = 9;
int incoming = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  
  //LCD pin declarations
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH);
  lcd.begin(16,2);  //initialize cols x rows of LCD display
   
  //blink LED once for 2s, sanity check
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);

  //diagnostic LCD code to ensure it's working
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Init Display");
  delay(1500);
  lcd.clear();
  delay(1000);
  lcd.print("Init Display");
  delay(1500);
  lcd.clear();
  
}

void loop()
{
  incoming = Serial.available();
  while (incoming == 0)                 //Keep checking until there is something available 
  {
    incoming = Serial.available();
  }

  val = Serial.parseInt();             //Reads integers as integer rather than ASCI. Anything else returns 0

  //print val to lcd display
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Val is ");
  lcd.print(val);


  for (int i = 0; i < val ; i++)      //Flash the LED the appropriate number of times
  {
    digitalWrite(led, HIGH);   
    delay(500);               
    digitalWrite(led, LOW);   
    delay(500);   
  }
  val = 0;
}

