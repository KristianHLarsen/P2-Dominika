#include <Wire.h>
//MEGA
int inputRF;       //input Radio Frequency
int inputSM;       // input serial monitor
#define OUTCHAR 20 //size of array for characters going out
#define INCHAR 20  //size of array for characters coming in
char inString[INCHAR];
byte outString[OUTCHAR];
int carStatus = 1; //1 = good to go,    0 = Car has stopped


void setup  () {
  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.setTimeout(30000);
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(30000);
  Serial.flush();
}

void receiveString() {
  if (Serial3.available() > 0 )
  {
    int modtaget;
    modtaget = Serial3.readBytesUntil('/', inString, INCHAR); //break karakter = 10 =return
    Serial3.flush();
    String str = String(inString);
    char startChar = str.charAt(0);
    if (startChar == '=') {
      splitUp(str, modtaget);
    }
    Serial.flush();
  }
}


void splitUp(String A, int modtaget )
{
  int startSeperator = A.indexOf('=') + 1;
  int slutSeperator = A.indexOf('!');
  String sub1 = A.substring(startSeperator, slutSeperator);
  int value = sub1.toInt();
  Serial.print("Modtaget: "); Serial.print(value); Serial.println();
}

void transmit1()
{
  outString[0] = carStatus;
  String tal = '#' + String(outString[0]) + '!' + '/';
  Serial3.print(tal);    // sender det der blev skrevet i serial monitor over RF
  Serial3.flush();
  Serial.print("Sendt: ");
  Serial.print(tal);
  Serial.println();
  delay(10);
}

void transmit2 ()  {
  if (digitalRead(3) == LOW) {
    carStatus = 0;
    outString[0] = carStatus;
    String tal = '#' + String(outString[0]) + '!' + '/';
    Serial3.print(tal);    // sender det der blev skrevet i serial monitor over RF
    Serial3.flush();
    Serial.print("Sendt: ");
    Serial.print(tal);
    Serial.println();
    delay(10);
  }
  else {
    carStatus = 1;
  }
}

void loop()
{
  receiveString();
  transmit2();
  transmit1();
  delay(5);
}

