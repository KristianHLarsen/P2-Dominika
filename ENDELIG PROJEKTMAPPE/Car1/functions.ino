void setupConfig() {
  Serial.begin(9600);
  pinMode(irPin, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void triggerSignal() {
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(irPin, HIGH);
    delayMicroseconds(13);
    digitalWrite(irPin, LOW);
    delayMicroseconds(13);
  }

  delayMicroseconds(300);    // Sikrer at modtageren altid sender ultralydssignal før afsenderen
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delay(200);
}

