//Inluding all the library for the servo
#include <Servo.h>

//PID input for DC motor
double distanceReal;
float motorPWMOutput;
int motorPTerm;
int motorITerm;
int motorDTerm;
int motorLimitMax = 18;
int motorLimitMin = -17;
int distanceGoal = 30;

//PID input for servo
double directionReal;
float servoPWMOutput;
int servoPTerm;
int servoITerm;
int servoDTerm;
int servoLimitMax = 18;
int servoLimitMin = -17;
int directionGoal;

//Pin configuration for all devices
const int trig1Pin = 40;
const int echo1Pin = 41;
const int trig2Pin = 42;
const int echo2Pin = 43;
int motorPWMPin = 7;
int IRrecieverpin = 4;

unsigned long measureStarttime;

Servo myservo;

void setup() {
  Serial.begin(9600);
  setupConfig();
}

void loop() {
  startFunction();
  motorSecurity();
}
