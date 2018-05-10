/*
   Fil der står for at modtage radiosignaler, samt splitte det ordentligt op.
*/


void radioSetup()
{
  Serial3.begin(9600);
}
char inString[4];


int receiveData() //Måske bare else(return 0;)?
{
  //if (Serial3.available() > 0)
  {
    //  Serial.println("Jeg er her");
    Serial3.readBytesUntil('/', inString, 4);
    String str = String(inString);
    Serial3.flush();
    char startChar = str.charAt(0);
    if (startChar == '#')
    {
      char carStatus = str.charAt(1);     // Serial.println("Status: " + String(carStatus));

      // carStatus = carStatus.toInt();
      if (carStatus == '0')  // Returnerer 0 til loop hvis der modtages et 0
      {
        //Serial.println("Status 1: " + String(carStatus));
        //Serial.println("0");
        return 0;
      }
      else if (carStatus == '1') // Returnerer 1 til loop hvis der modtages et 1
      {
        //Serial.println("Status 2: " + String(carStatus));

        //Serial.println("1");
        return 1;
      }
    }
  }
}

