
void recieve(){
int modtaget;
  Serial1.println("indtast fornavn   ");
  modtaget = Serial1.readBytesUntil(10, inString, NRCHAR - 1); //break karakter til at modtage er 10(return). -1 fordi der skal vaere et 0 til sidst.
  inString[modtaget] = 0; // afslutning paa tekststreng
  copyString(nr007.fornavn, inString);//kopire over i struct.

  Serial1.println("indtast efternavn   ");
  modtaget = Serial1.readBytesUntil(10, inString, NRCHAR - 1); //break karakter til at modtage er 10(return). -1 fordi der skal vaere et 0 til sidst.
  inString[modtaget] = 0; // afslutning paa tekststreng
  copyString(nr007.efternavn, inString);//kopire over i struct.

  Serial.print("My name is ");
  Serial.print(nr007.fornavn); Serial.print(" ");
  Serial.println(nr007.efternavn);

  if (0 == strcmp("James", nr007.fornavn) && 0 == strcmp("Bond", nr007.efternavn))
      Serial1.println("Pas Paa");
}

void sendstring(){
  
}

