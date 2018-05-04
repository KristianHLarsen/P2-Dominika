int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR2 20
#define OUTCHAR2 20
char instring[NRCHAR2];
byte outString[NRCHAR2];
volatile bool carStop = false;

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial.setTimeout(30000);
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(10000);
  Serial.flush();
}

void loop()
{
  transmit();
  delay(100);
  receiveString2();
  delay(100);
}


void receiveString2() {
  if (Serial3.available() > 0 )
  {
    int modtaget; 
    modtaget = Serial3.readBytesUntil('/', instring, NRCHAR2); //break karakter = 10 =return
    Serial3.flush();
    String str = String(instring);
    char startChar = str.charAt(0);
    if (startChar == '#') {
      splitUp(str, modtaget);
    }
    Serial3.flush();
  }
}

void splitUp(String A, int modtaget )
{ 
  int seperatorEt = A.indexOf('!');
  String sub1 = A.substring(0, seperatorEt);
  int sub2 = sub1.toInt();
  Serial.println("Modtaget: " + sub2);
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

