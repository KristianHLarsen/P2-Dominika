void setup() {
  Serial.begin(9600);
  Serial.setTimeout(30000); // timeout paa 3 sekunder.
  Serial1.begin(9600);
  Serial1.setTimeout(30000);
  pinMode(2,OUTPUT);
}

#define NRCHAR 15
#define NRPULS 12

char inString[NRCHAR];

// NB vi printer hele array naar
void printString(char *pStr)
{
  for (int i = 0; i < NRCHAR; i++) {
    Serial.print(*pStr);
    pStr ++;
  }

}

struct personTp {
  char fornavn[NRCHAR];
  char efternavn[NRCHAR];
  int pulsMaalinger[NRPULS];
};

struct personTp nr007;


void copyString(char *dest, char *src) {

  while (*src != 0) {
    *dest = *src; // vi får pointeren tuk at pege det samme sted.
    dest = dest + 1; // dest = dest + 1 er det samme som bare at skrive dest++
    src++;
  }
  *dest = *src; // eller *dest=0; fordi *src peger på 0
}



void printStringLgt(char *pStr, int lgt) {

  for (int i = 0; i < lgt ; i ++) {
    Serial.print(*pStr, HEX); Serial.print("   ");
    pStr++;
  }
  Serial.println("  ");
}




void loop() {
  recieve();
  

  delay(1000);
}




/*&(instring[0]) = &(*(inString + 0 = &*inString = inString

*/
