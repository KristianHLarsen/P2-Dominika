int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 20
#define OUTCHAR 100
char instring[NRCHAR];
byte outString[3] = {111, 22, 1};



void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(30000);
  //Serial.print("WR_433920_3_9_0_0");
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(10000);
  Serial.flush();
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
}

