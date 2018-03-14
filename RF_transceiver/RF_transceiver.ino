//MEGA
int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 15
char inString[NRCHAR];
char breakcaractor ='!';


void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(30000);
  //Serial.print("WR_433920_3_9_0_0");
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(30000);
  Serial.flush();
}

void loop()
{
  receiveString();
  transmit();
  
}

void receive()
{
  while (Serial3.available()){
    }
    inputRF = Serial3.read();   //serial 3 er koblet til RF modul
    Serial.write(inputRF);      // skriver til Serial monitor
    Serial.println();
    Serial.println("Modtaget data"); 
}


void transmit()
{
  while (Serial.available() )
  {
    inputSM = Serial.read();   // læser  hvad der bliver skrevet i Serial monitor
    Serial3.write(inputSM);    // sender det der blev skrevet i serial monitor over RF
    Serial.write(inputSM);     // udskriver det samme på serial monitor
    Serial.println();
    Serial.println("Sendt data");
  }
}



void receiveString(){

  int modtaget;
  Serial.println("Indtast en streng");
  modtaget = Serial3.readBytesUntil('breakcaractor', inString, NRCHAR); //break karakter til 
  Serial3.flush();
  Serial.print("modtaget antal:  "); Serial.println(modtaget);
  printString(inString); //som er &(instring[0]) = inString

}








