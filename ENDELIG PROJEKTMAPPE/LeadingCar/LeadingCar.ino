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
char instring[NRCHAR];
byte outString[3] = {111, 22, 1};
int carStop = 1; //carStop status. 1 = driving. 1 = STOP

int motorVal;
int INa = 7;
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
  pinMode(INa, OUTPUT); //DIR
  pinMode(INb, OUTPUT); //DIR
  digitalWrite(INa, HIGH);
  digitalWrite(INb, LOW);
  myservo.attach(9);
}

void loop()
{
  while (millis() - lastMillis < 200) // Der læses kun RF i 200 millisekudner, hvorefter der foretages en måling ved ultralyd
  {
    receiveString(); // RF
  }
  triggerSignal(); // ULTRALYD
}

void RFNextCar(int x)  { // Funktionen der afsender data til næste bil. x er enten 1 eller 0
  String tal = '#' + String(x) + '!' + '/';
  Serial3.print(tal);    // sender det der blev skrevet i serial monitor over RF
  Serial.println(""); Serial.print("String sent to next car: "); Serial.print(tal); Serial.println("");
  Serial3.flush();
  delay(10);
}

void receiveString() {
  if (Serial3.available() > 0 )
  {
    Serial3.readBytesUntil('/', instring, NRCHAR); //break karakter = 10 = return
    Serial3.flush();
    String str = String(instring);
    char startChar = str.charAt(0);
    if (startChar == '=') {
      splitUp(str);
      RFmillis = millis(); //reset RFmillis
    }

void splitUp(String A )
{
  int startSeperator = A.indexOf('=') + 1;
  int seperatorEt = A.indexOf('!');
  int seperatorTo = A.indexOf('!', seperatorEt + 1);
  int seperatorTre = A.indexOf('/');
  String sub1 = A.substring(startSeperator, seperatorEt);
  String sub2 = A.substring(seperatorEt + 1, seperatorTo);
  String sub3 = A.substring(seperatorTo + 1, seperatorTre);

  int PWM_H_bridge = sub1.toInt();
  int PWM_Servo = sub2.toInt();
  int carStop = sub3.toInt();

  if ( carStop != 0)  {
    RFNextCar(1);
    Serial.println(""); Serial.print("If Carstop = 1"); Serial.println("");
    servoControl(PWM_Servo);
    motorControl(PWM_H_bridge);
  }

  if (carStop == 0) {
    Serial.println(""); Serial.print("if Carstop = 0"); Serial.println("");
    analogWrite(pwmpin, 0);
    myservo.write(85);
    RFNextCar(0);
  }
}

