void setup()
{
  
  Serial.begin(9600);
}

void loop()
{
  double humid = random(20);
  double temp = random(10);
  Serial.print(temp);
  Serial.print(",");
  Serial.print(humid);
  Serial.print(",");
  Serial.flush();
  delay(1000);
}


