#include <Servo.h>

/*
 * Dette program bruges til førerbilen i platoonet. 
 * Funktionen er at modtage data fra controlleren og sende en start- eller stopkommando videre
 * til platooning-bilen. 
 * Programmet modtager data fra controlleren, som den omregner til PWM-værdier til motorerne, 
 * hvorefter der afsendes data til bagvedkørende.
 */

int inputRF; // input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 20
#define OUTCHAR 100
char instring[NRCHAR]; //array for received data. 
byte outString[3] = {111, 22, 1}; //array with our data. 
int carStop = 1; //carStop status. 1 = driving. 0 = STOP

int motorVal;
int INa = 7;  // Direction on DC motor
int INb = 6;
int pwmpin = 5;
int motorSpeed; //Motorspeed. Min. value: 30.  Max. value: 255
int servoVal;

int irPin = 2;
const int trigPin = 3;
const int echoPin = 4;

unsigned long RFmillis;
long lastMillis;

// defines variables
long duration;
int distance;
int start = 0;
int slut = 0;

Servo myservo;

void setup()
{
  millis();
  lastMillis = 0;
  Serial.begin(9600);
  Serial.setTimeout(30000);
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(10000);
  Serial.flush();
  setupConfig();
  pinMode(pwmpin, OUTPUT);
  pinMode(INa, OUTPUT); //DIR pin
  pinMode(INb, OUTPUT); //DIR pin
  digitalWrite(INa, HIGH);
  digitalWrite(INb, LOW);
  myservo.attach(9);
}

void loop()
{
  while (millis() - lastMillis < 200) // Read RF for 200 ms, then meassure ultrasonic sensor one time. 
  {
    receiveString(); //RF
  }
  triggerSignal(); //ULTRASONIC
}

void RFNextCar(int x)  {                // Function for sending a stop or start signal to next car. 0 = stop, 1 = drive/start
  String tal = '#' + String(x) + '!' + '/';
  Serial3.print(tal);                              //Send "tal" with the RF-module. 
  Serial.println(""); Serial.print("String sent to next car: "); Serial.print(tal); Serial.println(""); //Serial print for debugging
  Serial3.flush();
  delay(10);
}

void receiveString() {
  if (Serial3.available() > 0 )
  {
    Serial3.readBytesUntil('/', instring, NRCHAR); //break character = /
    Serial3.flush();
    String str = String(instring);
    char startChar = str.charAt(0);                //Check the first character in the array
    if (startChar == '=') {                        //If the start-character is correct, proceed to analyze the data.
      splitUp(str);                                //split up the received string
    }

void splitUp(String A ) //Function for splitting up the received string. Using seperators, it makes 3 substrings and converts them to ints. 
{
  int startSeperator = A.indexOf('=') + 1; 
  int seperatorEt = A.indexOf('!');
  int seperatorTo = A.indexOf('!', seperatorEt + 1);
  int seperatorTre = A.indexOf('/');
  String sub1 = A.substring(startSeperator, seperatorEt);
  String sub2 = A.substring(seperatorEt + 1, seperatorTo);
  String sub3 = A.substring(seperatorTo + 1, seperatorTre);

  int PWM_H_bridge = sub1.toInt(); //value for motorspeed
  int PWM_Servo = sub2.toInt(); //value for servo
  int carStop = sub3.toInt(); //carStop

  if ( carStop != 0)  { //function for sending the drive/start-signal to the next car. If stopCar = 1, proceed to control the motors.
    RFNextCar(1);
    Serial.println(""); Serial.print("If Carstop = 1"); Serial.println(""); //serial print for debugging
    servoControl(PWM_Servo);
    motorControl(PWM_H_bridge);
  }

  if (carStop == 0) { //function for sending the stop signal to the next car. If stopCar = 0, stop this car and correct steering. 
    Serial.println(""); Serial.print("if Carstop = 0"); Serial.println("");
    analogWrite(pwmpin, 0);
    myservo.write(85);
    RFNextCar(0);
  }
}

