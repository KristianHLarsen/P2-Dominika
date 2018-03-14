//MEGA
int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
void setup()
{
  Serial.begin(9600);
  //Serial.print("WR_433920_3_9_0_0");
  Serial.flush();
}

void loop()
{
  receive();
  transmit();
}

void receive()
{
  if (Serial3.available() > 0 )
  {
    inputRF = Serial3.read();   //serial 3 er koblet til RF modul
    Serial.write(inputRF);      // skriver til Serial monitor
    Serial.println();
    Serial.println("Modtaget data");
  }
}


void transmit()
{
  if (Serial.available() > 0 )
  {
    inputSM = Serial.read();   // læser  hvad der bliver skrevet i Serial monitor
    Serial3.write(inputSM);    // sender det der blev skrevet i serial monitor over RF
    Serial.write(inputSM);     // udskriver det samme på serial monitor
    Serial.println();
    Serial.println("Sendt data");
  }
}
