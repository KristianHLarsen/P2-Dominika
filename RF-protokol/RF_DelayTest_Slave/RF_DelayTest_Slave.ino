int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR2 20
#define OUTCHAR2 20
char instring[NRCHAR2];
byte outString[NRCHAR2];

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(30000);
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(10000);
  Serial.flush();
}

void loop()
{
  transmit();
  delay(200);
  receiveString2();
  delay(200);
}


void receiveString2() {
  if (Serial3.available() > 0 )
  {

    int modtaget;
    modtaget = Serial3.readBytesUntil('/', instring, NRCHAR2); //break karakter = 10 =return
    Serial3.flush();
    String str = String(instring);
    splitUp(str, modtaget);
    Serial.flush();
  }
}

void splitUp(String A, int modtaget )
{

  int seperatorEt = A.indexOf('!');
  String sub1 = A.substring(0, seperatorEt);

  // int PWM_H_bridge = sub1.toInt();

  // Serial.println("Modtaget: " + String(PWM_H_bridge));
  Serial.println("Modtaget: " + String(sub1));
}

//void printString(char *pStr)
//{
//  Serial.print("Modtaget    ");
//  for (int i = 0; i < NRCHAR2; i++) {
//    Serial.print(*pStr);
//    pStr++;
//  }
//  Serial.println();
//}

void transmit()
{
  outString[0] = 2;

  String tal = '=' + String(outString[0]) + '?' + '/';
  Serial3.print(tal);    // sender det der blev skrevet i serial monitor over RF
  Serial3.flush();
  Serial.println(tal);
  delay(10);
}

