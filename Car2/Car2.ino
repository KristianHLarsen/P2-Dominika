/*
 * SKAL LAVES:
 * 
 * Indsættes kode i forhold til ultralyd
*/

int motorPWMOutput;
unsigned long errors[10];
unsigned long accumulator;
unsigned long PIDVal;
int propVal;
int intVal;
int derVal;
int divider;
int distanceVal;
float distanceReal;




void setup() {
  
  Serial.begin(9600);

}

void loop() {
  findError();
  PIDCal();


}
