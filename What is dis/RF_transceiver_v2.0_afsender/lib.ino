
void printString(char *pStr)
{
  Serial.print("Modtaget    ");
  for (int i = 0; i < NRCHAR; i++) {
    Serial.print(*pStr);
    pStr++;
  }
Serial.println();
<<<<<<< HEAD
}
=======
}
>>>>>>> 1bb0914d32695a11c22f80f698a40253e73621d1
