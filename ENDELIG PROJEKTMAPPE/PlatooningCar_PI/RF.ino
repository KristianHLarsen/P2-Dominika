/*
   Fil der står for at modtage radiosignaler, samt splitte det ordentligt op.
*/


void radioSetup()
{
  Serial3.begin(9600);
}
char inString[4];


int receiveData()                               // int: Returns a 0 or a 1
{
  {
    Serial3.readBytesUntil('/', inString, 4);   // Read until break character
    String str = String(inString);              // Put it in a string
    Serial3.flush();
    char startChar = str.charAt(0);             // Read the first character
    if (startChar == '#')                       // If the first character is correct, proceed to analyze. 
    {
      char carStatus = str.charAt(1);           // Set the carstatus to either "stop" or "drive" (0 or 1)
      if (carStatus == '0')                     // Returns 0 to loop if the signal contains zero. 
      {
        return 0;
      }
      else if (carStatus == '1')                // Returns 1 to loop if the signal contains one. 
      {
        return 1;
      }
    }
  }
}

