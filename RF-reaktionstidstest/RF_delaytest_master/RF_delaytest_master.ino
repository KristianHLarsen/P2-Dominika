#include <Wire.h>
//MEGA
int inputRF;       //input Radio Frequency
int inputSM;       // input serial monitor
#define OUTCHAR 20 //size of array for characters going out
#define INCHAR 20  //size of array for characters coming in
char inString[INCHAR];
byte outString[OUTCHAR];
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
  String tal = '#' + String(outString[0]) + '!' + '/';
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
    char a = Serial3.read();
    if (a == '=') {
      int modtaget;
      modtaget = Serial3.readBytesUntil('/', inString, INCHAR); //break karakter = 10 =return
      Serial3.flush();
      String str = String(inString);
      splitUp(str, modtaget);
      Serial.flush();
    }
  }
  else  {
    //do nothing
  }
}

void splitUp(String A, int modtaget )
{
  int seperatorEt = A.indexOf('?');
  String sub1 = A.substring(0, seperatorEt);
  //test = sub1.toInt(); 
  //Serial.println("Modtaget: " + String(test));
  Serial.println("Modtaget: " + String(sub1));
}

void timer()  {
  transmit();
  tStart = micros(); // Time in milliseconds since start
  receiveString2();
  while (Serial3.available() == 0)  {
    //No code - just busy waiting
  }
  tStop = micros(); // Time in milliseconds since stop
  tReak =  tStop - tStart;
  Serial.print("Forsinkelse: ");
  Serial.print(tReak);  Serial.print(" micro s");
  Serial.println();
  Serial.println();
}

void loop()
{
  timer();
  delay(1000);
}

