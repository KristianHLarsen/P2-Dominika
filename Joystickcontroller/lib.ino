void printString(char *pStr, int channel)
{
  if (channel == 0) {

    Serial.print("Modtaget    ");
    for (int i = 0; i < NRCHAR; i++) {
      Serial.print(*pStr);
      pStr++;
    }
    Serial.println();
  }
  if (channel == 3) {
    for (int i = 0; i < NRCHAR; i++) {
      Serial3.write(*pStr);
      pStr++;
    }
  }
}

void receiveString() {
  if (Serial3.available() > 0 )
  {
    int modtaget;
    Serial.println("Indtast en streng");
    modtaget = Serial3.readBytesUntil(10, inString, NRCHAR); //break karakter = 10 =return
    Serial3.flush();
    Serial.print("modtaget antal:  "); Serial.println(modtaget);
    
    printString(inString, 0); //som er &(instring[0]) = inString
  }
}


void transmitString() {
  if (Serial.available() > 0 )
  {
    int modtaget;
    Serial.println("Indtast streng");
    modtaget = Serial.readBytesUntil(10, outString, NRCHAR); //break karakter = 10 =return
    Serial.flush();
    Serial.print("modtaget antal:  "); Serial.println(modtaget);
    printString(outString, 3); //som er &(instring[0]) = inString
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

void receive()
{
  while (Serial3.available() ) {
  }
  inputRF = Serial3.read();   //serial 3 er koblet til RF modul
  Serial.write(inputRF);      // skriver til Serial monitor
  Serial.println();
  Serial.println("Modtaget data");
}
