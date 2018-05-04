const int trig1Pin = 40;
const int echo1Pin = 41;

const int trig2Pin = 42;
const int echo2Pin = 43;

int PWM_PIN = 7;
double PWM = 0;
double distance = 0;
double goal = 40;

double angle;
double servoGoal = 90;
double servoPWM = 0;

unsigned long tid;

float gennemsnit[4];
int gCount = 0;



void setupConfig() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig1Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo1Pin, INPUT); // Sets the echoPin as an Input
  pinMode(trig2Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo2Pin, INPUT); // Sets the echoPin as an Input
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

}


void setup() {
  // put your setup code here, to run once:
pinMode(12,OUTPUT);
pinMode(4,INPUT); 
setupConfig();
}

void loop() {
  // put your main code here, to run repeatedly:
transmit();
/*if (digitalRead(4)== LOW) {
  digitalWrite(12,HIGH);
  Serial.println("forbindelse");
  
}*/
//digitalWrite(12,LOW);
}
void transmit()
{
  if(digitalRead(4)== LOW)
  {
    //Serial.println("jjj");
   //digitalWrite(12,LOW); 
      delayMicroseconds(20);  //Soerger for at eliminere problemer med forsinkelse fra når der bliver triggeret et signal.
     
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
      measure();
  }
}



void measure() {
delayMicroseconds(800); //100
  unsigned long echo1Start = micros();
  unsigned long echo1Slut = 0;
  unsigned long echo1Time;

  unsigned long echo2Start = micros();
  unsigned long echo2Slut = 0;
  unsigned long echo2Time;

  bool trigBool1 = false;
  bool trigBool2 = false;

  bool readyBool1 = false;
  bool readyBool2 = false;


  while (1) {
    int val1 = digitalRead(echo1Pin); // Fortæller om echopin er høj eller lav
    int val2 = digitalRead(echo2Pin);
   /*while (val1 == 0 && trigBool1 == false)       // While loop der sikrer at der ikke bliver målt en uhensigtsmæssig LOW, ved forsinkelse på modulet
   {
      val1 = digitalRead(echo1Pin);
      val2 = digitalRead(echo2Pin);
  
    }*/
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
      echo1Time = echo1Slut - echo1Start;
      echo2Time = echo2Slut - echo2Start;
      Serial.println("Sensor 1: " + String(echo1Time * 0.034) + "    Start: " + String(echo1Start) + "    Slut: " + String(echo1Slut));
      Serial.println("Sensor 2: " + String(echo2Time * 0.034) + "    Start: " + String(echo2Start) + "    Slut: " + String(echo2Slut));
    float forskel = (echo1Time*0.034 - echo2Time*0.034);
    gennemsnit[gCount] = forskel;
    gCount++;
    if(gCount == 4)
    {
      //Serial.println(forskel);
      float gSnit = (gennemsnit[0] + gennemsnit[1] + gennemsnit[2] + gennemsnit[3])/4;
      Serial.println(gSnit);
      gCount = 0;
    }
      delay(80);
      break;                                                 // While loopet stoppes da målingerne er færdige
    }
  }
}
  




