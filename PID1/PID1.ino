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



Servo myservo;
PID distancePID(&distance, &PWM, &goal, 0.9, 0, 0, P_ON_E, REVERSE);
PID servoPID(&angle, &servoPWM, &servoGoal, 1, 0, 0, P_ON_E, DIRECT);
PID servo1PID(&angle, &servoPWM, &servoGoal, 1, 0, 0, P_ON_E, REVERSE);


void setup() {

  setupConfig();

}

void loop() {

  transmit();

}
