//EMG Demo. 
//Turn LED on when you flex muscle (i.e. if Analog signal > threshold)
//Miran / 7/09/14

const int LED = 9;
const int emgIn = A0;

int EMG_THRESHOLD = 600;  //change as necessary

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(300);  
}//end setup

void loop() {

  int emgValue = analogRead(emgIn);  //sample EMG sensor
  Serial.println(emgValue);

  if (emgValue > EMG_THRESHOLD) {
     digitalWrite(LED, HIGH); 
  } 
  else {
     digitalWrite(LED, LOW); 
  }
  
  
}//end loop
