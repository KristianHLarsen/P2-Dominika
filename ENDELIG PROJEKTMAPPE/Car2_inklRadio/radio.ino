void radioSetup()
{
  Serial3.begin(9600);
}
char inString[4];


int receiveData()
{
  if (Serial3.available() > 0)
  {
    //  Serial.println("Jeg er her");
    Serial3.readBytesUntil('/', inString, 4);
    String str = String(inString);
    Serial.println(str);
    char startChar = str.charAt(0);
    if (startChar == '#')
    {

      char carStatus = str.charAt(1);     // Serial.println("Status: " + String(carStatus));

      // carStatus = carStatus.toInt();

      if (carStatus == '0')
      {
        Serial.println("Status1: " + String(carStatus));
        //Serial.println("0");
        return 0;
      }
      else if (carStatus == '1')
      {
                Serial.println("Status2: " + String(carStatus));

        //Serial.println("1");
        return 1;
      }
    }
  }
}

