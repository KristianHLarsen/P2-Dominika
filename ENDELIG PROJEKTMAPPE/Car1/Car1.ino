
#include <Servo.h>

int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 20
#define OUTCHAR 100
char instring[NRCHAR];
byte outString[3] = {111, 22, 1};
int carStop = 1; //car stop status. 1 = driving. 1 = STOP

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
  //Serial.print("WR_433920_3_9_0_0");
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
  while (millis() - lastMillis < 200)
  {
    receiveString();
  }
  if ((millis() - RFmillis) < 300)  {
    triggerSignal();
  }
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
  }
  else if ((millis() - RFmillis) > 300) {
    analogWrite(pwmpin, 0); //0 speed
    myservo.write(85);      //correct fault steering
  }
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

    if ((millis() - RFmillis) < 300)  {
      servoControl(PWM_Servo);
      motorControl(PWM_H_bridge);
    }

    if (carStop == 0) {
      analogWrite(pwmpin, 0);
      myservo.write(85);
    }
    else {
      carStop = 1;
    }

  }

