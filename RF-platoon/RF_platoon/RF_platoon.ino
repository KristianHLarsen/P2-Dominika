int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define INCHAR 20
#define OUTCHAR 20
char inString[INCHAR];
byte outString[OUTCHAR];

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial.setTimeout(30000);
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(10000);
  Serial.flush();
  pinMode(7, OUTPUT);
}

void receiveString() {
  if (Serial3.available() > 0 )
  {
    int modtaget;
    modtaget = Serial3.readBytesUntil('/', inString, INCHAR); //break karakter = 10 =return
    Serial3.flush();
    String str = String(inString);
    char startChar = str.charAt(0);
    if (startChar == '#') {
      splitUp(str, modtaget);
    }
    Serial3.flush();
  }
}

void splitUp(String A, int modtaget )
{
  int startSeperator = A.indexOf('#') + 1;
  int slutSeperator = A.indexOf('!');
  String sub1 = A.substring(startSeperator, slutSeperator);
  int value = sub1.toInt();
  Serial.print("Modtaget: "); Serial.print(value); Serial.println();
}

void transmit()
{
  outString[0] = 2;
  String tal = '=' + String(outString[0]) + '!' + '/';
  Serial.print("Sendt: ");
  Serial.print(tal);
  Serial3.print(tal); // sender det der blev skrevet i serial monitor over RF
  Serial.println();
  Serial3.flush();
  delay(10);
}

void tjekStatus() {
  int modtaget;
    modtaget = Serial3.readBytesUntil('/', inString, INCHAR); //break karakter = 10 =return
    Serial3.flush();
    String str = String(inString);
  char startChar = str.charAt(1);
  if (startChar == '0') {
    digitalWrite(7, HIGH);
  }
  else {
    digitalWrite(7, LOW);
  }

}

void loop()
{
  receiveString();
  transmit();
  tjekStatus();
  delay(5);
}

