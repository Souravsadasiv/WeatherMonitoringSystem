int sensorPin = A0;   // select the analog input pin for the photoresistor

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(sensorPin));
  delay(200);
}