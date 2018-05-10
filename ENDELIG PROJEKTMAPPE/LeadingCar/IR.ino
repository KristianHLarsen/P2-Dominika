/*
 * This file sends the IR-pulse. 
 */

void setupConfig() {
  pinMode(irPin, OUTPUT);
  pinMode(trigPin, OUTPUT);    // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);     // Sets the echoPin as an Input
}

void triggerSignal() {
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(irPin, HIGH);
    delayMicroseconds(13);
    digitalWrite(irPin, LOW);
    delayMicroseconds(13);
  }

  delayMicroseconds(300);      // Ensures that the receiving car always sends an ultrasonic signal before the sender. 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  Serial.println("IR sendt");  //serial print for debugging. 
  lastMillis = millis();

