void setupConfig() {
  Serial.begin(9600);
  pinMode(trig1Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo1Pin, INPUT); // Sets the echoPin as an Input
  pinMode(trig2Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo2Pin, INPUT); // Sets the echoPin as an Input
  pinMode(PWM_PIN, OUTPUT);

  myservo.attach(9);
}

void GetError(void) {
  byte i = 0;
  // shift error values
  for (i = 9; i > 0; i--)
    Error[i] = Error[i - 1];
  // load new error into top array spot
  Error[0] = (long)distanceReal-(long)distanceGoal;
}

void CalculatePID(void) {
  // Set constants here
  PTerm = 200;
  ITerm = 25;
  DTerm = 100;
  Divider = 10;

  // Calculate the PID
  PIDValue = Error[0] * PTerm;   // start with proportional gain
  Accumulator += Error[0];  // accumulator is sum of errors
  PIDValue += ITerm * Accumulator; // add integral gain and error accumulation
  PIDValue += DTerm * (Error[0] - Error[9]); // differential gain comes next
  PIDValue = PIDValue >> Divider; // scale PID down with divider

  // limit the PID to the resolution we have for the PWM variable
  if (PIDValue >= 127)
    PIDValue = 127;
  if (PIDValue <= -126)
    PIDValue = -126;

  //PWM output should be between 1 and 254 so we add to the PID
  PWMOutput = PIDValue + 127;
}


void transmit() {
  int tal = analogRead(A10);   //Tjekker først om der modtages en puls. Når den puls slutter og går LOW fortsætter koden
  while (tal > 900)
  {
    tal = analogRead(A10);

    if (tal < 800) {
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

    if (echo1Slut != 0 && echo2Slut != 0)                     // Er der målt en sluttid på begge sensorer, kaldes en funktion der udskriver distanceRealr på Serial monitor
    {
      //Serial.println(9);
      echo1Time = echo1Slut - echo1Start;
      echo2Time = echo2Slut - echo2Start;
      distanceReal = (echo1Time * 0.034 + echo2Time * 0.034) / 2;
      break;                                                 // While loopet stoppes da målingerne er færdige
    }
  }
}


