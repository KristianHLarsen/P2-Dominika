//UNO
int input;
void setup()
{
  Serial.begin(9600);
  //Serial.print("WR_433920_3_9_0_0");
  Serial.flush();
}

void loop()
{
 //sendforesprøgsel
 //modtag bekræftigelse



  
  //Serial.print(1);

  if (Serial.available() > 0)
  {
    input = Serial.read();
    Serial.println(input);

  }
  //delay(1000);
}
