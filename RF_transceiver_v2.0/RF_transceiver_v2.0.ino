//MEGA
int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 100
#define OUTCHAR 100
char inString[NRCHAR];
byte outString[3] = {111,22,1};

    String tal = String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '/';


void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(30000);
  //Serial.print("WR_433920_3_9_0_0");
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(30000);
  Serial.flush();
  splitUp();
}

void loop()
{
 // receiveString();
  //transmit();

}

void receive()
{
  if (Serial3.available() > 0) {
  }
  inputRF = Serial3.read();   //serial 3 er koblet til RF modul
  Serial.write(inputRF);      // skriver til Serial monitor
  Serial.println();
  Serial.println("Modtaget data");
}

void transmit()
{
    String tal = String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '/';
    Serial3.print(tal);    // sender det der blev skrevet i serial monitor over RF
    Serial3.flush();
    Serial.println();
    Serial.println("Sendt data");
    delay(1000);
}

void receiveString() {

  if (Serial3.available() > 0)
  {
    int modtaget;
    Serial.println("Indtast en streng og slut med !");
    modtaget = Serial3.readBytesUntil(10, inString, NRCHAR); //break karakter til
    Serial3.flush();
    Serial.print("modtaget antal:  "); Serial.println(modtaget);
    printString(inString); //som er &(instring[0]) = inString
  }
}

void splitUp()
{
  int seperatorEt = tal.indexOf('!');
  int seperatorTo = tal.indexOf('!',seperatorEt+1);
  int seperatorTre = tal.indexOf('/');
  String sub1 = tal.substring(0,seperatorEt);
  String sub2 = tal.substring(seperatorEt+1,seperatorTo);
  String sub3 = tal.substring(seperatorTo+1, seperatorTre);

  Serial.println(sub1);
  Serial.println(sub2);
  Serial.println(sub3);
}

