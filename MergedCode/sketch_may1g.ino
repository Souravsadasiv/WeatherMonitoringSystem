// ltr data 5v gnd
#include <dht11.h>
#define DHT11PIN 4

dht11 DHT11;
const int sensor_pin = A1;
int sensorPin = A0;

void  setup()
{
  Serial.begin(9600);
 
}

void loop()
{

//photoregister
Serial.print("Light intensity : ");
  Serial.println(analogRead(sensorPin));

//moisture
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  //Serial.print("%\n\n");
  Serial.println();
//dht
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);
  Serial.println("--------------------------------------------------------------------------");

  delay(1000);

}