
void printString(char *pStr)
{
  Serial.print("Modtaget    ");
  for (int i = 0; i < NRCHAR; i++) {
    Serial.print(*pStr);
    pStr++;
  }
Serial.println();
}
