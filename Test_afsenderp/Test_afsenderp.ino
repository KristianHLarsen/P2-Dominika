/*Førerbil kode (afsender)
   LED
   Knap til afsendelse
*/
#define trigPin 5
#define LED 12
#define knap 2

void sendPuls() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

}


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(knap, INPUT_PULLUP);
  pinMode(trigPin, INPUT);

}

void loop() {

  if (digitalRead(knap) == LOW) {

    digitalWrite(LED, HIGH);
    sendPuls();
    delay(2000);
    digitalWrite(LED, LOW);
  }



}
