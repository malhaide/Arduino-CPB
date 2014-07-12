//Arduino Pro

int led = 9;

void setup() {
  pinMode(led, OUTPUT);
  
}//end setup

void loop() {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}//end loop
