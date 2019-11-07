
int photoresistor_pin = A1;
int microphone_pin = A0;
int output_pin = 5;
int LED = 13;

int photoresistor;
int hPhotoresistor;
int microphone;
int hMicrophone;


int photoresistor_tres = 30; //minus
int microphone_tres = 300;   //plus


int measure = 1;

long int hTime;

void setup() {
  Serial.begin(9600);
  pinMode(photoresistor_pin, INPUT_PULLUP);
  pinMode(microphone_pin, INPUT);
  pinMode(output_pin, OUTPUT);
  digitalWrite(13, 0);
  analogWrite(output_pin, 0);
}

boolean photoresistor_treshold(int value) {
  if (value <= photoresistor_tres) {
    return true;
  }
  else {
    return false;
  }
}

boolean microphone_treshold(int value) {
  if (value >= microphone_tres) {
    return true;
  }
  else {
    return false;
  }
}

void time_snap() {
  hTime = millis();
}

float time_count() {
  int finalTime = millis() - hTime;
  float distance = (340.3 * finalTime) / 1000;
  return distance;
}


void outMe(float value) {
  float newVal = 53.57 * value;
  analogWrite(output_pin, int(newVal));
}



void loop() {
  photoresistor = analogRead(photoresistor_pin);
  microphone = analogRead(microphone_pin);

  Serial.print(photoresistor);
  Serial.print("  |  ");
  Serial.println(microphone);
  
  if (measure == 1) {
    if (photoresistor_treshold(photoresistor)) {
      measure = 2;
      time_snap();
      digitalWrite(LED,HIGH);
    }
  }
  if (measure == 2) {
    if (microphone_treshold(microphone)) {
      outMe(time_count());
      digitalWrite(LED,LOW);
    }
  }


}
