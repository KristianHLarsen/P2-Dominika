//Inluding all the library for the servo
#include <Servo.h>

// Der skal rettes  hvor tit bil 2 modtager fra bil 1.  Den misser mange datapakker,
//som gør at der er stor forsinkelse på at den reagere i forhold til hvornår man trykker på kill switch

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
int motorPTerm = 1;
int motorITerm = 0;
int motorDTerm = 0;
int motorLimitMax = 18;
int motorLimitMin = -17;
int distanceGoal = 25;

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

//Global variables for the avareage calculator that controls steering
float avarage[4];
int aCount = 0;

//Global variable for the function that checks if any IR signal has been received
unsigned long measureStarttime;

int value;
Servo myservo;

void setup() {
  Serial.begin(9600);
  setupConfig();
  radioSetup();
  Serial3.setTimeout(10000);
  Serial3.begin(9600);
}

void StopFunction() {
  if (Serial3.available() > 0)
  {
    value = receiveData();
    if (value == 0) // Stopper bilen
    {
      Serial.println("StopCar = " + String(value));
      analogWrite(motorPWMPin, 0);
      myservo.write(125);
    }

  }
}

void loop() {
  if (Serial3.available() > 0)
  {
    value = receiveData();
    Serial.println("Data modtaget: " + String(value));

    if (value == 0) // Stopper bilen
    {
      //Serial.println("StopCar = 0");
      analogWrite(motorPWMPin, 0);
      myservo.write(125);
    }

    if (value == 1) // Platooner
    {
      //Serial.println("StopCar = 1");
      startFunction();
      motorControl();
      // myservo.write(95);
    }
  }

}
