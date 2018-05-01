#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

float h;
float t;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  dht.begin();
}

void loop() {
  delay(1000);

measureArray(dht.readHumidity(), h);
measureArray(dht.readTemperature(), t);


  String message = "#" + String(h) + "," + String(t);

  Serial.println(message);
}

