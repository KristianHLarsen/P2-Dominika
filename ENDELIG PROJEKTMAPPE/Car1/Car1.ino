
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
  triggerSignal();
}

void RFNextCar(int x)  {
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
    //Serial.println(""); Serial.print("Received string: "); Serial.print(str); Serial.println("");
    char startChar = str.charAt(0);
    if (startChar == '=') {
      Serial.println("HER");
      splitUp(str);
      RFmillis = millis(); //reset RFmillis
    }
  }
 /* if ((millis() - RFmillis) > 300) {
    analogWrite(pwmpin, 0); //0 speed
    myservo.write(85);      //correct fault steering
    RFNextCar(0);
    Serial.println(""); Serial.print("Lost connection for more than 300 ms"); Serial.println("");
 }*/
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
    Serial.println(carStop);
  if ( carStop != 0)  {
        RFNextCar(1);
Serial.println("STOP 1");
    servoControl(PWM_Servo);
    motorControl(PWM_H_bridge);
  }

  if (carStop == 0) {
    Serial.println("STOP 0");
      analogWrite(pwmpin, 0);
      myservo.write(85);
      RFNextCar(0);
  }
}

