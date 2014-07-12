//Bitalino (analog) Accelerometer (simple) Sketch
//Accelerometer Leveler. Certain orientation lights up the LED
//Miran 7/9/14
//Digital Accelerometer Ranges (10-bit Digital ADC Values)
// 300 < X < 460
// 300 < Y < 460
// 300 < Z < 460

//declare pins
const int X_pin = A2;
const int Y_pin = A1;
const int Z_pin = A0;
  
int x_val, y_val, z_val;  //x,y, and z dig values
  
int LED = 9;  

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  
}//end setup

void loop() {
  //sample x,y, and z and display on serial monitor
  x_val = analogRead(X_pin);
  y_val = analogRead(Y_pin);
  z_val = analogRead(Z_pin);
  
  //display to serial monitor
  Serial.print("X = ");
  Serial.print(x_val);  
  Serial.print(" Y = ");
  Serial.print(y_val);    
  Serial.print(" Z = ");
  Serial.println(z_val);   

  //light LED when ACC. is Flat (aka parallel with the ground)
  if (x_val >= 360 && x_val <= 400 && y_val >= 360 && y_val <= 380 && z_val >= 440 && z_val <= 460) {
     //LED = on 
      digitalWrite(LED, HIGH);
  }
    else {
      //LED = Off 
      digitalWrite(LED, LOW);
    }
  
  
//  delay(1000);
  
}//end loop
