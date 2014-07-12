//Echo command back to user via Rx(pin 0) and Tx (pin 1) on Arduino
//using HC-06 module and UART Serial port on Arduino ^

String command = "";

void setup()
{
  Serial.begin(9600);
    
  Serial.println("Serial connection Established!");
    
}//end setup

void loop()
{
  if (Serial.available()) {
    while(Serial.available()) {
    command += (char)Serial.read();  //read serial bytes from user
     
  }//end while
  
  Serial.println(command);    //echo back
  
  //reset command
  command = "";
  }//end if avail
  
  delay(1000);
}//end loop
