

int LDR_Pin = A0; //analog pin 0

int LED = 13;

void setup(){
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

}
void loop(){
  int LDRReading = analogRead(LDR_Pin); 

  Serial.println(LDRReading);
  delay(250); //just here to slow down the output for easier reading

  if (LDRReading < 100)
  {
     digitalWrite(LED, HIGH); 
  }
  else {
     digitalWrite(LED, LOW); 
  }


}//end loop


