int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 20
#define OUTCHAR 100
char instring[NRCHAR]; 
byte outString[3] = {111, 22, 1};

//String tal = String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '/';


void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(30000);
  //Serial.print("WR_433920_3_9_0_0");
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(10000);
  Serial.flush();
  //splitUp();
}

void loop()
{
  receiveString2();
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
    instring = Serial3.read(); //break karakter til
    Serial3.flush();
    Serial.println(instring);
   Serial.print("modtaget antal:  "); //Serial.println(modtaget);
   // printString(inString); //som er &(instring[0]) = inString
    splitUp();
  }
}

void receiveString2() {
  if (Serial3.available() > 0 )
  {
    int modtaget;
    Serial.println("Indtast en streng");
    modtaget = Serial3.readBytesUntil('/', inString, NRCHAR); //break karakter = 10 =return
    Serial3.flush();
    Serial.print("modtaget antal:  "); Serial.println(modtaget);
   // printString(inString, 0); //som er &(instring[0]) = inString
   String str = String(instring);
   Serial.print(str);
   //splitUp(str);
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

  Serial.println(sub1);
  Serial.println(sub2);
  Serial.println(sub3);
}

