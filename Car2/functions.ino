void setupConfig() {
  Serial.begin(9600);
  pinMode(trig1Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo1Pin, INPUT); // Sets the echoPin as an Input
  pinMode(trig2Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo2Pin, INPUT); // Sets the echoPin as an Input
  pinMode(13, OUTPUT);
  pinMode(motorPWMpin, OUTPUT);
  digitalWrite(13, LOW);
  myservo.attach(9);
}

void transmit() {
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

    if (echo1Slut != 0 && echo2Slut != 0)                     // Er der målt en sluttid på begge sensorer, kaldes en funktion der udskriver distancer på Serial monitor
    {
      //Serial.println(9);
      echo1Time = echo1Slut - echo1Start;
      echo2Time = echo2Slut - echo2Start;
      distance = (echo1Time * 0.034 + echo2Time * 0.034) / 2;
      break;                                                 // While loopet stoppes da målingerne er færdige
    }
  }
}

void PIDMotor(int propVal, int intVal, int derVal, int distanceVal) {

  unsigned long errors[10];
  unsigned long accumulator;
  unsigned long PIDVal;

  int i = 0;
  int divider = 10;

  propVal;
  intVal;
  derVal;

  //finding error below

  for (i = 9; i > 0; i--)
    errors[i] = errors[i - 1];
  // load new error into top array spot
  errors[0] = (long)distanceVal - (long)distanceReal;

  //calculating PID below

  PIDVal = errors[0] * propVal;   // start with proportional gain
  accumulator += errors[0];  // accumulator is sum of errors
  PIDVal += intVal * accumulator; // add integral gain and error accumulation
  PIDVal += derVal * (errors[0] - errors[9]); // differential gain comes next
  PIDVal = PIDVal >> divider; // scale PID down with divider

  if (PIDVal >= 127)
    PIDVal = 127;
  if (PIDVal <= -126)
    PIDVal = -126;

  //PWM output should be between 1 and 254 so we add to the PID
  motorPWMOutput = PIDVal + 127;

}

