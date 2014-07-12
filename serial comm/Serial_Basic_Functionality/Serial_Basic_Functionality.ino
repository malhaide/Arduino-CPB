//Serial Test Basic Function


void setup() {
  Serial.begin(115200);  
  Serial.println("Serial Connection Ready");  
  
}//end setup

void loop() {
  int avail = Serial.available();
  Serial.print("Serial.available() = ");
  Serial.println(avail);
 
  
  
}//end loop
