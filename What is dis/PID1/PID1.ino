#include <Servo.h>
#include <PID_v1.h>
#include <math.h>

const int trig1Pin = 40;
const int echo1Pin = 41;

const int trig2Pin = 42;
const int echo2Pin = 43;

int PWM_PIN = 7;
double PWM = 0;
double distance = 0;
double goal = 40;

double angle;
double servoGoal = 90;
double servoPWM = 0;

unsigned long tid;



Servo myservo;
PID distancePID(&distance, &PWM, &goal, 2, 0, 0, P_ON_E, REVERSE);
PID servoPID(&angle, &servoPWM, &servoGoal, 1, 0, 0, P_ON_E, DIRECT);
PID servo1PID(&angle, &servoPWM, &servoGoal, 1, 0, 0, P_ON_E, REVERSE);


void setup() {

  setupConfig();

}

void loop() {
//Serial.println(analogRead(A10));
  transmit();
  
 
if (millis() - tid > 1000) // Tid bliver sat = millis hvergang at transmit koerer. 
  {
    analogWrite(PWM_PIN, 0);
  }

}
