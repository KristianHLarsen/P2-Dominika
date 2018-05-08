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
float servoPWMOutput;
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
int IRrecieverpin = 5;

float avarage[4];
int aCount = 0;


unsigned long measureStarttime;

Servo myservo;

void setup() {
  Serial.begin(9600);
  setupConfig();
  radioSetup();
  Serial3.setTimeout(10000);
  Serial3.begin(9600);
}

void loop() {
if(Serial3.available() > 0)
{
int value = receiveData();
  Serial.println("Data: " + String(value));

   if (value == 1)
  {
    Serial.println("Her");
    startFunction();
    motorControl();
 // myservo.write(95); 
  }
  
  if (value == 0)
  {
    Serial.println("Ikke her");
    analogWrite(motorPWMPin, 0);
    myservo.write(125);
  }
}

}
