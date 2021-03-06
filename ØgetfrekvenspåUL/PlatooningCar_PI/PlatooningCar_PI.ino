//Inluding all the library for the servo
#include <Servo.h>

// Der skal rettes  hvor tit bil 2 modtager fra bil 1.  Den misser mange datapakker,
// som gør at der er stor forsinkelse på at den reagere i forhold til hvornår man trykker på kill switch

/* Dette er programmet der kører på arduino på følgebilen, altså bil nummer 2.
   I loop ventes der på at der modtages et signal fra bilen foran. Modtages der 0, stoppes bilen, og der
   lyttes efter nye RF signaler.
   Modtages der et 1 tal, begynder programmet at vente på at der bliver modtaget IR puls,
   som bruges til at synkronisere ultralydssensorerne.
   Når ultralyd er afsendt, startes der en timer. Timeren stoppes når der modtages et
   signal på echoPin på den tilsvarende sensor.
   Forskellen på de to afstande bruges til at regulere servomotoren,
   mens gennemsnittet af afstanden bruges til at syre DC-motoren

   Bilen stopper hvis den ikke har modtaget RF signal indenfor 500 ms
*/


//PID input for DC motor
double distanceReal;
float motorPWMOutput;
float motorPTerm = 0.9;
float motorITerm = 0.03;
int motorLimitMax = 30;
int motorLimitMin = -17;
int distanceGoal = 35;

//PID input for servo
float directionReal;
float servoPWMOutput;
int servoPTerm = 2;
int servoITerm = 0;
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
const int badMeasurement = 13;

//Global variables for the avareage calculator that controls steering
float avarage[4];
int aCount = 0;

//Global variable for the function that checks if any IR signal has been received
unsigned long measureStarttime;

int value;
Servo myservo;
//GLOBAL VALUES FOR DEBUGGING
unsigned long loopCount=0; 
unsigned long badMeasure=0;

void setup() {
  Serial.begin(9600);
  setupConfig();
  radioSetup();
  Serial3.setTimeout(10000);
  Serial3.begin(9600);
  myservo.write(105);                              // Correct the steering
  //analogWrite(motorPWMPin, 100);
}

void StopFunction() {
  if (Serial3.available() > 0)
  {
    value = receiveData();        // Make a value with the int from receiveData() (either 0 or 1)
    if (value == 0)               // If the stop-signal is received
    {
      //Serial.println("StopCar = " + String(value));   // Serial print for debugging.
      analogWrite(motorPWMPin, 0);                    // Stop the car
      myservo.write(125);                             // Correct the steering
    }

  }
}

void loop() {  
  
  if (Serial3.available() > 0)
  {
    value = receiveData();
    //Serial.println("Data modtaget: " + String(value)); // Serial print for debugging

    if (value == 0)                                    // If the stop-signal is received, stop the car and correct the steering
    {
      myservo.write(110);                              // Correct the steering

      analogWrite(motorPWMPin, 0);                     // Stop the car
    }

    if (value == 1)                                    // If start-signal is received
    {
      startFunction();                                 // Run the platooning-functions
      motorControl();                                  // Run the motorcontrol
    }
  }
}
