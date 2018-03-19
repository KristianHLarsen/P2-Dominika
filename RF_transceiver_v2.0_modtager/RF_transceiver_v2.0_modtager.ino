<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 5d069c3d500bb230ce1924ad4bc631728a6e7ecb
#include <Servo.h>

int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 20
#define OUTCHAR 100
char instring[NRCHAR];
byte outString[3] = {111, 22, 1};

int motorVal;
int dirpin = 11;
int pwmpin = 6;
int motorSpeed; // midsteværdi 25 dog maks. 255
int servoVal;


Servo myservo;  
void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(30000);
  //Serial.print("WR_433920_3_9_0_0");
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(10000);
  Serial.flush();

  pinMode(dirpin, OUTPUT);
  pinMode(pwmpin, OUTPUT);
  myservo.attach(9);
}

void loop()
{
  receiveString2();

}


void receiveString2() {
  if (Serial3.available() > 0 )
  {
    int modtaget;
    modtaget = Serial3.readBytesUntil('/', instring, NRCHAR); //break karakter = 10 =return
    Serial3.flush();
    String str = String(instring);
    splitUp(str);
  }
}



void splitUp(String A )
{
<<<<<<< HEAD
=======

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
  motorControl(PWM_H_bridge);
}

=======
#include <Servo.h>

int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 20
#define OUTCHAR 100
char instring[NRCHAR];
byte outString[3] = {111, 22, 1};

int motorVal;
int dirpin = 11;
int pwmpin = 6;
int motorSpeed; // midsteværdi 25 dog maks. 255
int servoVal;


Servo myservo;  
void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(30000);
  //Serial.print("WR_433920_3_9_0_0");
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(10000);
  Serial.flush();

  pinMode(dirpin, OUTPUT);
  pinMode(pwmpin, OUTPUT);
  myservo.attach(9);
}

void loop()
{
  receiveString2();

}


void receiveString2() {
  if (Serial3.available() > 0 )
  {
    int modtaget;
    modtaget = Serial3.readBytesUntil('/', instring, NRCHAR); //break karakter = 10 =return
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
  motorControl(PWM_H_bridge);
}
>>>>>>> 1bb0914d32695a11c22f80f698a40253e73621d1
=======
#include <Servo.h>

int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 20
#define OUTCHAR 100
char instring[NRCHAR];
byte outString[3] = {111, 22, 1};

int motorVal;
int dirpin = 11;
int pwmpin = 6;
int motorSpeed; // midsteværdi 25 dog maks. 255
int servoVal;


Servo myservo;  
void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(30000);
  //Serial.print("WR_433920_3_9_0_0");
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(10000);
  Serial.flush();

  pinMode(dirpin, OUTPUT);
  pinMode(pwmpin, OUTPUT);
  myservo.attach(9);
}

void loop()
{
  receiveString2();

}


void receiveString2() {
  if (Serial3.available() > 0 )
  {
    int modtaget;
    modtaget = Serial3.readBytesUntil('/', instring, NRCHAR); //break karakter = 10 =return
    Serial3.flush();
    String str = String(instring);
    splitUp(str);
  }
}



void splitUp(String A )
{

>>>>>>> 5d069c3d500bb230ce1924ad4bc631728a6e7ecb
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
  motorControl(PWM_H_bridge);
}
<<<<<<< HEAD
=======
>>>>>>> 1bb0914d32695a11c22f80f698a40253e73621d1
>>>>>>> 5d069c3d500bb230ce1924ad4bc631728a6e7ecb
