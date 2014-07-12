//Heart Beat Tracker
//Hardware: Arduino Pro (3.3V) + ECG Bitalino Sensor
//see evernote for more details
//Written by Miran Alhaideri (7/8/14)

int LED = 9;
int LED_PACE = 5;

int iterations = 0;  //count the # of iterations. Loop ~100 Hz
int bpm_count = 0;  //holds your heart beat count

extern volatile unsigned long timer0_millis;
const int analogIn = A1;


int sensorValue = 0;


int dt = 5;


int scnt = 0;
int ssum = 0;


int msum = 0;


int dcnt = 0;
int dsum = 0;


int tcnt = 0;


int aux = 0;


int brightness = 0;
int fadeAmount = 2;


int beatThreshold = 600; // might be user dependant.


const int wlen = 4;


void setup() {
  Serial.begin(115200); 
  
  pinMode(LED, OUTPUT);
  pinMode(LED_PACE, OUTPUT);
}


void loop() {
  sensorValue = analogRead(analogIn);
  
  if (scnt == wlen) {
    aux = ssum - msum;
    
    if (aux < 0) {
      aux = abs(aux);
    }


    if (dcnt == wlen) {
      if (dsum > beatThreshold) {
        brightness = 255;
        bpm_count++;    //count your heart beats
      }
      
      dcnt = 0;
      dsum = 0;
    }


    dsum = dsum + aux;
    dcnt = dcnt + 1;
    
    msum = ssum;
    
    scnt = 0;
    ssum = 0;


  }
  
  if (brightness > 0) {
    brightness = brightness - fadeAmount;
  }
  
  ssum = ssum + sensorValue;
  scnt = scnt + 1;
    
  analogWrite(LED, brightness);
  
  Serial.print(sensorValue);
  Serial.println(',');
  
  delay (dt-millis());
  
  timer0_millis = 0;
  
  //print heart rate based on #beats in past ten iterations
  iterations++;
  
  if (iterations % 100 == 0) {
      Serial.print("bpm_count = ");
      Serial.println(bpm_count);
      bpm_count = 0;  //reset bpm
     
     /* 
      //synchronise to blink every 1sec. Trying to figure out loop speed
      digitalWrite(LED_PACE, HIGH);
      delay(250);
      digitalWrite(LED_PACE, LOW);
      */
  }
  
}
