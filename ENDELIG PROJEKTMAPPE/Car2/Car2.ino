//Inluding all the library for the servo
#include <Servo.h>

//PID input for DC motor
double distanceReal;
float motorPWMOutput;
int motorPTerm = 1;
int motorITerm = 0;
int motorDTerm = 0;
int motorLimitMax = 18;
int motorLimitMin = -17;
int distanceGoal = 35;

//PID input for servo
float directionReal;
float servoOutput;
int servoPTerm = 5;
int servoITerm = 0;
int servoDTerm = 0;
int servoLimitMax = 200;
int servoLimitMin = 100;
int directionGoal;
int servoVal;

//Pin configuration for all devices
const int trig1Pin = 52;
const int echo1Pin = 53;
const int trig2Pin = 22;
const int echo2Pin = 23;
int directionPin = 7;
int motorPWMPin = 6;
int IRreceiverpin = 5;

//Global variables for the avareage calculator that controls steering
float avarage[4];
int aCount = 0;

//Global variable for the function that checks if any IR signal has been received
unsigned long measureStarttime;

Servo myservo;

void setup() {
  Serial.begin(9600);
  setupConfig();
}

void loop() {
  startFunction();
  motorControl();
}
