
#include <Servo.h>

int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 20
#define OUTCHAR 100
char instring[NRCHAR];
byte outString[3] = {111, 22, 1};

int motorVal;
//int dirpin = 11;
int INa = 7;
int INb = 6;
int pwmpin = 5;
int motorSpeed; // midsteværdi 25 dog maks. 255
int servoVal;

int irPin = 2;
const int trigPin = 3;
const int echoPin = 4;

long lastMillis;

// defines variables
long duration;
int distance;
int start = 0;
int slut = 0;



Servo myservo;

void setup()
{
  lastMillis = 0;
  Serial.begin(9600);
  Serial.setTimeout(30000);
  //Serial.print("WR_433920_3_9_0_0");
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(10000);
  Serial.flush();
  setupConfig();
  //pinMode(dirpin, OUTPUT);
  pinMode(pwmpin, OUTPUT);
  pinMode(INa, OUTPUT);
  pinMode(INb,OUTPUT);
    digitalWrite(INa,HIGH);
    digitalWrite(INb,LOW);
  myservo.attach(9);
}

void loop()
{
  while (millis() - lastMillis < 200)
  {
    receiveString();
  }
  triggerSignal();
}

void receiveString() {
  if (Serial3.available() > 0 )
  {
    Serial3.readBytesUntil('/', instring, NRCHAR); //break karakter = 10 =return
    Serial3.flush();
    String str = String(instring);
    splitUp(str);
  }
}



void splitUp(String A )
{
  int seperatorEt = A.indexOf('!');
  int seperatorTo = A.indexOf('!', seperatorEt + 1);
  int seperatorTre = A.indexOf('/');
  String sub1 = A.substring(0, seperatorEt);
  String sub2 = A.substring(seperatorEt + 1, seperatorTo);
  String sub3 = A.substring(seperatorTo + 1, seperatorTre);

  int PWM_H_bridge = sub1.toInt();
  int PWM_Servo = sub2.toInt();
  int DIR_H_bridge = sub3.toInt();

  Serial.println(PWM_H_bridge);
  Serial.println(PWM_Servo);
  Serial.println(DIR_H_bridge);

  servoControl(PWM_Servo);
  motorControl(PWM_H_bridge, DIR_H_bridge);
}

