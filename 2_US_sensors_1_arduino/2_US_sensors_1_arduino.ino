/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
// defines pins numbers
const int trig1Pin = 6; //fuck u, Kristian
const int echo1Pin = 7;

const int trig2Pin = 8;
const int echo2Pin = 9;

// defines variables
long duration;
int distance;
bool echo1Bool = true;
int echo1Start;
int echo1Slut;
int echo1Time;

bool echo2Bool = true;
int echo2Start;
int echo2Slut;
int echo2Time;

bool trigBool1 = false;
bool trigBool2 = false;



void setup() {
pinMode(trig1Pin, OUTPUT); // Sets the trigPin as an Output
pinMode(echo1Pin, INPUT); // Sets the echoPin as an Input
pinMode(trig2Pin, OUTPUT); //
pinMode(echo2Pin, INPUT); //
Serial.begin(9600); // Starts the serial communication
}

void sensor1()
{
   digitalWrite(trig1Pin, LOW);

delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig1Pin, HIGH);

delayMicroseconds(10);
digitalWrite(trig1Pin, LOW);
meas1();
}

void meas1()
{
  while(true)
  {
  if(digitalRead(echo1Pin) == HIGH && echo1Bool == true)
{
  echo1Start = micros(); 
  echo1Bool = false;
}
if(digitalRead(echo1Pin) == LOW && echo1Bool == false)
{
  echo1Slut = micros();
  echo1Bool = true;

  echo1Time = echo1Slut - echo1Start;  
  Serial.print("Distance 1:  ");
  Serial.println(echo1Time*0.034/2);
  trigBool1 = true;
  sensor2();
}

}
}

void sensor2()
{
   digitalWrite(trig2Pin, LOW);

delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig2Pin, HIGH);

delayMicroseconds(10);
digitalWrite(trig2Pin, LOW);
meas2();
}

void meas2()
{
  while(true){
  if(digitalRead(echo2Pin) == HIGH && echo2Bool == true)
{
  echo2Start = micros(); 
  echo2Bool = false;
}
if(digitalRead(echo2Pin) == LOW && echo2Bool == false)
{
  echo2Slut = micros();
  echo2Bool = true;

  echo2Time = echo2Slut - echo2Start;  
  Serial.print("Distance 2:  ");
  Serial.println(echo2Time*0.034/2);
  trigBool2 = true;
  sensor1();
}
  }
}

void loop() {
  sensor1();}



