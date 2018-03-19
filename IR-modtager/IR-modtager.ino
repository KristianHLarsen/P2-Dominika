/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
// defines pins numbers
const int trigPin = 6;
const int echoPin = 7;
// defines variables
long duration;
int distance;

int IRIn = 3;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(IRIn,INPUT_PULLUP);
Serial.begin(9600); // Starts the serial communication
}
void loop() {

int tal = analogRead(A0);
while(tal < 200)
{
   tal = analogRead(A0);

  if(tal > 800){
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
//Serial.print("Distance: ");
if(distance < 38)
{
Serial.println(distance);
}
break;
}}
}
