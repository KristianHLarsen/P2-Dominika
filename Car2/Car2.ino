/*
   SKAL LAVES:

   Indsættes kode i forhold til ultralyd
*/
#include <Servo.h>
#include <math.h>

const int trig1Pin = 40;
const int echo1Pin = 41;
const int trig2Pin = 42;
const int echo2Pin = 43;
const int motorPWMpin = 3;
const int servoPWMpin = 2;
const int dirPin = 4;

int motorDir = 0;
double distance;

unsigned long tid;

double distanceReal = 0;
double motorPWMOutput;
double servoOutput;


Servo myservo;

void setup() {
  setupConfig();

}

void loop() {
  PIDMotor(2000, 0, 10, 40);
  transmit();
  if (millis() - tid > 1000) {
    analogWrite(motorPWMpin, 0);
  }
}
