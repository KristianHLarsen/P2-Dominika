#include <Wire.h>
//MEGA
int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 100
#define OUTCHAR 100
#define NRCHAR2 20
char inString[NRCHAR2];
int outString[1];
float tStart;
float tStop;
float tReak;
int test;

void setup  () {
  Serial.begin(9600);
  Serial.setTimeout(30000);
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(30000);
  Serial.flush();
}

void transmit()
{
  outString[0] = 1;
  String tal = String(outString[0]) + '!' + '/';
  Serial3.print(tal);    // sender det der blev skrevet i serial monitor over RF
  Serial3.flush();
  Serial.print("Sendt: ");
  Serial.print(tal);
  Serial.println();
  delay(10);
}

void receiveString2() {
  if (Serial3.available() > 0 )
  {
    int modtaget;
    modtaget = Serial3.readBytesUntil('/', inString, NRCHAR2); //break karakter = 10 =return
    Serial3.flush();
    String str = String(inString);
    splitUp(str, modtaget);
    Serial.flush();
  }
  else  {
    //do nothing
  }
}

void splitUp(String A, int modtaget )
{
  int seperatorEt = A.indexOf('?');
  String sub1 = A.substring(0, seperatorEt);
  test = sub1.toInt();
  Serial.println("Modtaget: " + String(test));
}

void timer()  {
  transmit();
  tStart = millis(); // Time in milliseconds since start
  receiveString2();
  while (Serial3.available() == 0)  {
    //No code - just busy waiting
  }
  tStop = millis(); // Time in milliseconds since stop
  tReak =  tStop - tStart;
  Serial.print("Forsinkelse: ");
  Serial.print(String(tReak) + " ms");
  Serial.println();
  Serial.println();
}


void loop()
{
  timer();
  delay(1000);
}

