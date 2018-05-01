//Initialising pins for devices
int irPin = 4;
const int trigPin = 6;
const int echoPin = 7;


// defines variables
long duration;
int distance;
int start = 0;
int slut = 0;


void setup() {

  setupConfig();
}

void loop() {

  triggerSignal();
}
