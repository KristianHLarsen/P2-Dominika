void setupConfig() {
  pinMode(irPin, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
}

void pulseLoop() {
  for (int i = 0; i < 100; i++) {
    digitalWrite(irPin, HIGH);
    delayMicroseconds(13);
    digitalWrite(irPin, LOW);
    delayMicroseconds(13);
  }

  delayMicroseconds(480);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delay(180);

}
