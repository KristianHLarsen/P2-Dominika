//17/3-2018

// Den hjemmelavede pulseIn() funktion er lavet for at begge ultralydssensorer kan måle samtidig
// Det er nødvendigt da tiden fra IR bliver afsendt til det bliver modtaget kan variere med over 100 mikrosekunder

/* Programmet kan måle fra en HC-SR04 til to andre, på 2 forskellige arduinoer.
 * Der måles først om der modtages en IR puls. Når pulsen SLUTTER, sættes de to modtager arduinoer igang med at afsende en puls.
 * Sluttiden findes når en echopin går LOW. Til sidst trækkes starttiden fra sluttiden og der omregnes til centimeter
 * 
 * 
 * 
 * 
 */
const int trig1Pin = 2;
const int echo1Pin = 3;

const int trig2Pin = 6;
const int echo2Pin = 7;

bool echo1Bool = true;
int echo1Start;
int echo1Slut;
int echo1Time;

bool echo2Bool = true;
int echo2Start;
int echo2Slut;
int echo2Time;

bool trigBool1 = false;
bool trigBool2 = false;

bool readyBool1;
bool readyBool2;



void printDist() // FUnktionen der udskriver på serial monitor
{
  echo1Time = echo1Slut - echo1Start;
  echo2Time = echo2Slut - echo2Start;
 // Serial.println("Dist 1: " + String(echo1Time * 0.034));
 // Serial.println("Dist 2: " + String(echo2Time * 0.034));
  Serial.println((echo1Time * 0.034 - echo2Time * 0.034));
  echo1Bool = true;
  echo2Bool = true;
  echo1Slut = 0;
  echo2Slut = 0;

  if (echo1Time > echo2Time)
  {
    digitalWrite(13, LOW);
  }

  else if (echo1Time <= echo2Time)  //Hvis sensor 1 er tættere på end sensor 2 lyser pin 13 LED'en
  {
    digitalWrite(13, HIGH);
  }


}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig1Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo1Pin, INPUT); // Sets the echoPin as an Input
  pinMode(trig2Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo2Pin, INPUT); // Sets the echoPin as an Input
  pinMode(13, OUTPUT);
}

void loop() {
  transmit();


}
void transmit()
{
  int tal = analogRead(A0);   //Tjekker først om der modtages en puls. Når den puls slutter og går LOW fortsætter koden
  while (tal < 200)
  {
    tal = analogRead(A0);

    if (tal > 800) {
      // Serial.println(1);
      digitalWrite(trig1Pin, LOW);
      digitalWrite(trig2Pin, LOW);


      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trig1Pin, HIGH);
      digitalWrite(trig2Pin, HIGH);


      delayMicroseconds(10);
      digitalWrite(trig1Pin, LOW);
      digitalWrite(trig2Pin, LOW);
      delayMicroseconds(480);
      prepareVariables();
    }
  }
}

void prepareVariables() 
{
  echo1Start = micros();          // startværdi, altså her echoPin går HØJ
  echo2Start = echo1Start;
  trigBool1 = false;              // booleans nulstilles
  trigBool2 = false;
  readyBool1 = false;
  readyBool2 = false;
  measure();
}

void measure()
{
  while (1)
  {
    int val1 = digitalRead(echo1Pin);
    int val2 = digitalRead(echo2Pin);

    while (val1 == 0 && trigBool1 == false)       // While loop der sikrer at der ikke bliver målt en uhensigtsmæssig LOW, ved forsinkelse på modulet
    {
      val1 = digitalRead(echo1Pin);
      val2 = digitalRead(echo2Pin);
    }
    trigBool1 = true;                             // boolean der bruges i firbindelse med ovenstående while-loop

    if (val1 == 0 && trigBool1 == true && readyBool1 == false) //Her går echo-porten LOW, og pulsen er derfor SLUT
    {
      echo1Slut = micros();
      readyBool1 = true;                                      // Sikrer at der kun bliver målt EN sluttid
    }

    if (val2 == 0 && trigBool1 == true && readyBool2 == false)  // Det samme med sensor nr. 2
    {
      echo2Slut = micros();
      readyBool2 = true;
    }

    if (echo1Slut != 0 && echo2Slut != 0)                     // Er der målt en sluttid på begge sensorer, kaldes en funktion der udskriver distancer på Serial monitor
    {
      //Serial.println(9);

      printDist();
      break;                                                 // While loopet stoppes da målingerne er færdige
    }
  }

}







