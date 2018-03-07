/* Modtagerbil (modtager)

*/

//config

#define echoPinV 53
#define echoPinH 52
#define trigPinV 49
#define trigPinH 48

#define LED 3


void klargoerSensor() {
/*  digitalWrite(trigPinH, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinH, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinH, LOW);
*/
 digitalWrite(trigPinV, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinV, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinV, LOW);

}

void inputTjek() {

  digitalWrite(trigPinV, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinV, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinV, LOW);
  
  while (digitalRead(echoPinV) == HIGH) {
    digitalWrite(LED, LOW);
  }
  digitalWrite(LED, HIGH);
  Serial.println("0");
 
}


void maalDifferenceMellemSensorer() {
  float TStart, tidV, tidH, differenceTid;
  TStart = micros();

  while (digitalRead(echoPinV) == HIGH or digitalRead(echoPinH) == HIGH) {
    //vent paa signal
  }
  if (digitalRead(echoPinV) == LOW) {
    tidV = micros();

  }

  if (digitalRead(echoPinH) == LOW) {
    tidH = micros();
  }
  differenceTid = tidV - tidH; // giver difference i microsekunder
  Serial.print("Difference"); Serial.println(differenceTid);
}

void setup() {
  Serial.begin(9600);
  pinMode(echoPinV, INPUT);
  pinMode(echoPinH, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {

  klargoerSensor();
  Serial.println("klar til at modtage");
  inputTjek();
  Serial.println("signalmodtaget");
  digitalWrite(LED, LOW);
  delay(1000);
  
  // digitalWrite(LED, HIGH);
  //maalDifferenceMellemSensorer();
  //digitalWrite(LED, LOW);
  //delay(2000);
}
