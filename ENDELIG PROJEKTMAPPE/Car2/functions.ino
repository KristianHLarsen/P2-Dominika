void setupConfig() {
  Serial.begin(9600);
  pinMode(trig1Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo1Pin, INPUT); // Sets the echoPin as an Input
  pinMode(trig2Pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo2Pin, INPUT); // Sets the echoPin as an Input
  pinMode(motorPWMPin, OUTPUT);
  pinMode(IRrecieverpin, INPUT);
  myservo.attach(9);
  pinMode(directionPin,OUTPUT);
  digitalWrite(directionPin,HIGH);
}

void motorPID() {
  long Error;
  long PIDValue;
  long accumulator;

  Error = (long)distanceReal - (long)distanceGoal;

  // Calculate the PID
  PIDValue = Error * motorPTerm;   // start with proportional gain
  accumulator += Error;  // accumulator is sum of Errors
  //PIDValue += motorITerm * accumulator; // add integral gain and Error accumulation
  //PIDValue += motorDTerm * Error; // differential gain comes next

  // limit the PID to the resolution we have for the PWM variable
  if (PIDValue >= motorLimitMax)
    PIDValue = motorLimitMax;
  if (PIDValue <= motorLimitMin)
    PIDValue = motorLimitMin;

  //PWM output should be between 1 and 254 so we add to the PID
  motorPWMOutput = PIDValue + 18;
}

void servoPID() {
  float Error;
  float PIDValue;
  long accumulator;

  directionGoal=0;

  Error = directionReal - float(directionGoal);

  // Calculate the PID
  PIDValue = Error * servoPTerm;   // start with proportional gain
  //accumulator += Error;  // accumulator is sum of Errors
  //PIDValue += servoITerm * accumulator; // add integral gain and Error accumulation
  //PIDValue += servoDTerm * Error; // differential gain comes next

  // limit the PID to the resolution we have for the PWM variable
  /*
  if (PIDValue >= servoLimitMax)
    PIDValue = servoLimitMax;
  if (PIDValue <= servoLimitMin)
    PIDValue = servoLimitMin;
*/
  //PWM output should be between 1 and 254 so we add to the PID
  servoPWMOutput = PIDValue;
}

void startFunction() {
  if (digitalRead(IRrecieverpin) == LOW)
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
    measureAndCalculate();
  }
}

void measureAndCalculate() {

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
      distanceReal = (echo1Time * 0.034 + echo2Time * 0.034) / 2;

      if (distanceReal < 100 && distanceReal > 10) {

        //Debugging lines
        //Serial.println("Sensor 1: " + String(echo1Time * 0.034) + "    Start: " + String(echo1Start) + "    Slut: " + String(echo1Slut));
        //Serial.println("Sensor 2: " + String(echo2Time * 0.034) + "    Start: " + String(echo2Start) + "    Slut: " + String(echo2Slut));
        Serial.print("PWM: "); Serial.println(servoPWMOutput);
        //Serial.print("Dist: "); Serial.println(distanceReal);

        motorPID();   // Calculate the PID output for the motor
        servoPID();   // Calculates the PID output for the servo

        //Puts 4 different measurements into an array and calculates the avarage
        float difference = (echo1Time * 0.034 - echo2Time * 0.034);
        avarage[aCount] = difference;
        aCount++;
        if (aCount == 2) {
          //Serial.println(difference);
          directionReal = (avarage[0] + avarage[1] + avarage[2] + avarage[3]) / 4;
          Serial.println(directionReal);
          aCount = 0;
        }
      }
      measureStarttime = millis();
      delay(80);
      break;                                                 // While loopet stoppes da målingerne er færdige
    }
  }
}

void motorControl() {
  //Makes sure the DC motor dosn't use a PWM signal under 20, because it's the minimal value for the motor to get running.
  if (motorPWMOutput < 20) {
    motorPWMOutput = 0;
  }
  analogWrite(motorPWMPin, motorPWMOutput);

  servoVal = map(servoPWMOutput, -20, 25, 85, 135);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(servoVal);                  // sets the servo position according to the scaled value

  //makes the car stop if no signal is received in 500 ms.
  if (millis() - measureStarttime > 500)
  {
    motorPWMOutput = 0;
    analogWrite(motorPWMPin, 0);
  }
}

