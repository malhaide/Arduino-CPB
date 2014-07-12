//Written by Miran Alhaideri (061614)
//Use to test the delay, sensitivity, of Pressure Sensor
//Simple Pressure Sensor Test that allows you to vary pressure sensitivity using a arbitrary sensor threshold
//if threshold is exceeded, then an LED is turned on.

//declare vars here
int led = 13;    //declare pin #13
#define A A0    //set sensor A to be analog A0
#define SENSOR_THRESHOLD 100    //arbitrary ADC threshold to trigger LED

void setup() {
 //called when sketch starts up or when you hit the reset pin
 //put variables, pin modes, etc. here
  
  Serial.begin(9600);
  
  pinMode(led, OUTPUT);   //sets the digital pin as output
  pinMode(A, INPUT_PULLUP);  //turn on pull-up resistor on A0 pin (default = high)
  
  //sanity check
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
}

void loop(){
  int sensorValue = analogRead(A);  //sample Analog Voltage on (b/t 0 and 1024)
  
  if (sensorValue < SENSOR_THRESHOLD)
  {
      //test
      Serial.println(sensorValue);
      digitalWrite(led, HIGH);
    
     
  }
  else {
     Serial.println(sensorValue);
     digitalWrite(led, LOW); 
  }
  
}//end loop
