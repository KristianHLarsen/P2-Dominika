int irPin = 4;

const int trigPin = 6;
const int echoPin = 7;
// defines variables
long duration;
int distance;


void setup() {
  // put your setup code here, to run once:
pinMode(irPin,OUTPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i = 0;i < 100; i++)
{
  digitalWrite(irPin,HIGH);
  delayMicroseconds(13);
  digitalWrite(irPin,LOW);
  delayMicroseconds(13);
}
delayMicroseconds(1000);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(70);
}
