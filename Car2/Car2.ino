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
const int servoPWM= 2;

float distanceReal = 0;
double motorPWMOutput;
double servoOutput;


Servo myservo;

void setup() {
  setupConfig();

}

void loop() {
  PIDMotor();
  PIDSteering();
  transmit();
  if (millis() - tid > 1000) {
    analogWrite(PWM_PIN, 0);
  }
}
