//This function is configuring the different pins and devices.
void setupConfig() {
  Serial.begin(9600);
  pinMode(trig1Pin, OUTPUT); //Sets the trigPin as an Output.
  pinMode(echo1Pin, INPUT); //Sets the echoPin as an Input.
  pinMode(trig2Pin, OUTPUT); //Sets the trigPin as an Output.
  pinMode(echo2Pin, INPUT); //Sets the echoPin as an Input.
  pinMode(motorPWMPin, OUTPUT); //Sets the motorPWMPin as an Output.
  pinMode(IRreceiverpin, INPUT); //Sets the IRreceiverpin as an Input.
  myservo.attach(9); //Sets the servo for using pin 9 as signal pin.
  pinMode(directionPin, OUTPUT); //Sets the directionPin as an Output.
  digitalWrite(directionPin, HIGH); //Makes the directionPin go high so that the car is driving forward.
}

//PID for the DC motor.
void motorPID() {
  long Error;
  long PIDValue;
  long accumulator;

  Error = (long)distanceReal - (long)distanceGoal;

  // Calculate the PID.
  PIDValue = Error * motorPTerm;   // start with proportional gain.
  accumulator += Error;  // accumulator is sum of Errors.
  //PIDValue += motorITerm * accumulator; // add integral gain and Error accumulation.
  //PIDValue += motorDTerm * Error; // differential gain comes next.

  // limit the PID to the resolution we have for the PWM variable.
  if (PIDValue >= motorLimitMax)
    PIDValue = motorLimitMax;
  if (PIDValue <= motorLimitMin)
    PIDValue = motorLimitMin;

  //Here we have the PID output plus the max limit we've made for it at the regulation above.
  motorPWMOutput = PIDValue + 18;
}

//PID for the servo.
void servoPID() {
  float Error;
  float PIDValue;
  long accumulator;

  directionGoal = 0;

  Error = directionReal - float(directionGoal);

  // Calculate the PID.
  PIDValue = Error * servoPTerm;   // start with proportional gain.
  //accumulator += Error;  // accumulator is sum of Errors.
  //PIDValue += servoITerm * accumulator; // add integral gain and Error accumulation.
  //PIDValue += servoDTerm * Error; // differential gain comes next.

  //Here's the PID output for the servo.
  servoOutput = PIDValue;
}

//This is the function that starts it all.
void startFunction() {

  //If the ir receiver gets a signal, it starts the function below which triggers a signal. This is because the HC-SR04 needs to send a signal, before it's echopin is ready to receive a signal.
  if (digitalRead(IRreceiverpin) == LOW)
  {
    delayMicroseconds(20); //Eliminates problems with delays, when a signal is triggered.
    digitalWrite(trig1Pin, LOW);
    digitalWrite(trig2Pin, LOW);


    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds.
    digitalWrite(trig1Pin, HIGH);
    digitalWrite(trig2Pin, HIGH);


    delayMicroseconds(10);
    digitalWrite(trig1Pin, LOW);
    digitalWrite(trig2Pin, LOW);

    //After the echo is ready, the next function for measuring ultrasonic values are ready to run.
    measureAndCalculate();
  }
}

//This function is making the measurements of the distance and the steering values for the PIDs.
void measureAndCalculate() {

  delayMicroseconds(800); //This delay is here to make sure that the echopin has gone to low, before a signal is sent to Car2 from Car1.

  //The start values for the variables is defined here.
  unsigned long echo1Start = micros();
  unsigned long echo1End = 0;
  unsigned long echo1Time;

  unsigned long echo2Start = micros();
  unsigned long echo2End = 0;
  unsigned long echo2Time;

  bool trigBool1 = false;
  bool trigBool2 = false;

  bool readyBool1 = false;
  bool readyBool2 = false;


  while (1) {
    int val1 = digitalRead(echo1Pin); //Tells if the echopin is high or low.
    int val2 = digitalRead(echo2Pin);

    trigBool1 = true; //Boolean that's used with the while loop above.

    if (val1 == 0 && trigBool1 == true && readyBool1 == false) //Here the echopin goes low, and therefore the measurement is done.
    {
      echo1End = micros();
      readyBool1 = true; // Makes sure that only one endtime is being measured.
    }

    //The same thing as above, is happening for sensor nr. 2.
    if (val2 == 0 && trigBool1 == true && readyBool2 == false)
    {
      echo2End = micros();
      readyBool2 = true;
    }

    if (echo1End != 0 && echo2End != 0) { //If there has been measured an endtime on both sensors, the the function will measure the distance and direction below.
      echo1Time = echo1End - echo1Start;
      echo2Time = echo2End - echo2Start;

      //The distance is measured here.
      distanceReal = (echo1Time * 0.034 + echo2Time * 0.034) / 2;

      //If the distance is between 100 and 10, the code will move on from here. This is to eliminate all the flickering values, that will occur from the ultrasonic sensors.
      if (distanceReal < 100 && distanceReal > 10) {

        //Debugging lines.
        //Serial.println("Sensor 1: " + String(echo1Time * 0.034) + "    Start: " + String(echo1Start) + "    End: " + String(echo1End));
        //Serial.println("Sensor 2: " + String(echo2Time * 0.034) + "    Start: " + String(echo2Start) + "    End: " + String(echo2End));
        //Serial.print("PWM: "); Serial.println(servoOutput);
        //Serial.print("Dist: "); Serial.println(distanceReal);

        motorPID();   //Calculate the PID output for the motor.
        servoPID();   //Calculates the PID output for the servo.

        //Puts 4 different measurements into an array and calculates the avarage.
        float difference = (echo1Time * 0.034 - echo2Time * 0.034); //Calculates the difference between the two sensors, to make a direction value callede difference.

        //With the difference between the two sensors the array is filled up with 4 values. After that an avarage is calculated which is the direction.
        avarage[aCount] = difference;
        aCount++;
        if (aCount == 1) {
          directionReal = (avarage[0] + avarage[1] + avarage[2] + avarage[3]) / 1;
          Serial.println(directionReal);
          aCount = 0;
        }
      }
      measureStarttime = millis();
      delay(80);
      break;                                                 // The while loop stops, because the measurements are done.
    }
  }
}


//This function makes sure all the mesured values, are being used for the motor and the servo.
void motorControl() {
  //Makes sure the DC motor dosn't use a PWM signal under 20, because it's the minimal value for the motor to get running.
  if (motorPWMOutput < 20) {
    motorPWMOutput = 0;
  }

  //Here the motor is getting the signal, for it to start running.
  analogWrite(motorPWMPin, motorPWMOutput);

  servoVal = map(servoOutput, -20, 25, 95, 125);     //Scales the value for the servo from the value that the PID calculates.
  myservo.write(servoVal);                  //Sets the servo position according to the scaled value.

  //Makes the car stop if no signal is received in 500 ms.
  if (millis() - measureStarttime > 500)
  {
    motorPWMOutput = 0;
    analogWrite(motorPWMPin, 0);
  }
}

