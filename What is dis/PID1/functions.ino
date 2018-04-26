

void setupConfig() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig1Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo1Pin, INPUT); // Sets the echoPin as an Input
  pinMode(trig2Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo2Pin, INPUT); // Sets the echoPin as an Input
  pinMode(13, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);

  distancePID.SetOutputLimits(0, 50);
  servoPID.SetOutputLimits(110, 145);
  servo1PID.SetOutputLimits(75, 110);
  distancePID.SetMode(AUTOMATIC);
  servoPID.SetMode(AUTOMATIC);
  servo1PID.SetMode(AUTOMATIC);

  digitalWrite(13, LOW);

  myservo.attach(9);
}

void printDist(int echo1Time, int echo2Time) // Funktionen der udskriver vinkel og pwm 
{
  double side1;
  double side2;
  double side3;
  double side4;
  double theta;


  side1 = (echo1Time * 0.034);
  side2 = (echo2Time * 0.034);
  side3 = (11.3);

  side4 = sqrt(((2*((side1) * (side1))) + ((2*(side2) * (side2))) - ((side3) * (side3))) / 4);

  theta = ((((side3 / 2) * (side3 / 2)) + ((side4) * (side4)) - ((side2) * (side2))) / (2 * (side3 / 2) * side4));

  angle = ((acos(theta)) * (180 / 3.14159265));

 //Serial.println(side1);
 //Serial.println(side2);
 //Serial.println(side3);
  //Serial.println(side4);
  //Serial.println(theta);
  

  distance = (echo1Time * 0.034 + echo2Time * 0.034) / 2; // Vi finder gennemsnit for den maalte afstand. 
  // Serial.println("Dist 1: " + String(echo1Time * 0.034));
  // Serial.println("Dist 2: " + String(echo2Time * 0.034));
  //Serial.print("Forskel: ");
  //Serial.println((echo1Time * 0.034 - echo2Time * 0.034));

  if (angle < servoGoal && angle > 45) {
    servoPID.Compute();
  }
  else if (angle > servoGoal && angle < 135 ) {
    servo1PID.Compute();
    servoPWM = map(servoPWM, 75,110, 110 ,75);
  }
 // Serial.println("Vinkel: " + String(angle));
 // Serial.println("PWM: " + String(servoPWM));
 

  distancePID.Compute();
  analogWrite(PWM_PIN, PWM);
  Serial.print("PWM for motor:   ");  Serial.println(PWM);
  Serial.print("Distance:   "); Serial.println(distance);
  
  myservo.write(servoPWM);


  if (distance > 25)
  {
    digitalWrite(13, LOW);
  }

  else if (distance <= 25)  //Hvis sensor 1 er tættere på end sensor 2 lyser pin 13 LED'en
  {
    digitalWrite(13, HIGH);
  }
tid = millis();
//delay(1000);

}

void transmit()
{
  int tal = analogRead(A10);   //Tjekker først om der modtages en puls. Når den puls slutter og går LOW fortsætter koden
  while (tal < 200)
  {
    tal = analogRead(A10);

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
      delayMicroseconds(480);  //Soerger for at eliminere problemer med forsinkelse fra når der bliver triggeret et signal.
      measure();
    }
  }
}



void measure() {

  unsigned long echo1Start = micros();
  unsigned long echo1Slut;
  int echo1Time;

  unsigned long echo2Start = micros();
  unsigned long echo2Slut;
  int echo2Time;

  bool trigBool1 = false;
  bool trigBool2 = false;

  bool readyBool1 = false;
  bool readyBool2 = false;


  while (1) {
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
      echo1Time = echo1Slut - echo1Start;
      echo2Time = echo2Slut - echo2Start;
      printDist(echo1Time, echo2Time);
      break;                                                 // While loopet stoppes da målingerne er færdige
    }
  }
}


