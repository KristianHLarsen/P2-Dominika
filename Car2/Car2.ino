#include <Servo.h>

byte PWMOutput;
long Error[10];
long Accumulator;
long PIDValue;
int PTerm;
int ITerm;
int DTerm;
byte Divider;

const int trig1Pin = 40;
const int echo1Pin = 41;
const int trig2Pin = 42;
const int echo2Pin = 43;

int PWM_PIN = 7;
double distanceReal;
word distanceGoal = 10;


Servo myservo;


void setup() {

  Serial.begin(9600);
  setupConfig();

}

void loop() {
  distanceReal=7;

  transmit();

  GetError();       // Get position error
  CalculatePID();   // Calculate the PID output from the error
  
  Serial.println(PWMOutput);
  analogWrite(PWM_PIN, PWMOutput);


  /* if (millis() - tid > 1000)
    {
     analogWrite(PWM_PIN, 0);
    }
  */
}
