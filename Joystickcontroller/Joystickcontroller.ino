//MEGA
int inputRF=0; //input Radio Frequency
int inputSM=0; // input serial monitor
#define NRCHAR 100

char inString[NRCHAR];
char outString[NRCHAR];


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(30000);
  //Serial.print("WR_433920_3_9_0_0");
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(30000);
  Serial.flush();
}

void loop() {


  
    receiveString();
  //transmitString();
  
  //receive();
  transmit();
}

