/*
  I denne fil foretages der målinger på ultralydssensoren, samt styring af motorerne
*/

//This function is configuring the different pins and devices.
void setupConfig() {
  Serial.begin(9600);
  pinMode(trig1Pin, OUTPUT);           // Sets the trigPin as an output
  pinMode(echo1Pin, INPUT);            // Sets the echoPin as an input
  pinMode(trig2Pin, OUTPUT);           // Sets the trigPin as an output
  pinMode(echo2Pin, INPUT);            // Sets the echoPin as an input
  pinMode(motorPWMPin, OUTPUT);
  pinMode(IRrecieverpin, INPUT);
  myservo.attach(9);
  pinMode(directionPin, OUTPUT);
  digitalWrite(directionPin, HIGH);
}

//PID for the DC motor.
void motorPID() {
  long Error;
  long PIDValue;
  long accumulator;

  Error = (long)distanceReal - (long)distanceGoal;

  // Calculate the PID
  PIDValue = Error * motorPTerm;            // start with proportional gain
  accumulator += Error;                     // accumulator is sum of Errors
  //PIDValue += motorITerm * accumulator;   // add integral gain and Error accumulation

  //Limit the PID to the resolution we have for the PWM variable
  if (PIDValue >= motorLimitMax)
    PIDValue = motorLimitMax;
  if (PIDValue <= motorLimitMin)
    PIDValue = motorLimitMin;

  motorPWMOutput = PIDValue + 18;         //Here we have the PID output plus the max limit
  //we've made for it at the regulation above.

}

//PID for the servo.
void servoPID() {
  float Error;
  float PIDValue;
  long accumulator;

  directionGoal = 0;

  Error = directionReal - float(directionGoal);

  // Calculate the PID
  PIDValue = Error * servoPTerm;          // start with proportional gain
  //accumulator += Error;                 // accumulator is sum of Errors
  //PIDValue += servoITerm * accumulator; // add integral gain and Error accumulation


  servoPWMOutput = PIDValue;              // Here's the PID output for the servo.
}


void startFunction() {                    //This is the function that starts it all.
  StopFunction();

  //If the IR receiver receives a signal, it starts the function below which triggers a signal.
  //This happens because the HC-SR04 needs to send a signal, before the echopin is ready to receive a signal.
  while (digitalRead(IRrecieverpin) == HIGH)
  {
  }
  {
    // Serial.println("Starttid for StartFunction");
    // Serial.println(millis());
    delayMicroseconds(20);                 //Eliminates problems with delays, when a signal is triggered.

    digitalWrite(trig1Pin, LOW);
    digitalWrite(trig2Pin, LOW);

    delayMicroseconds(2);

    digitalWrite(trig1Pin, HIGH);
    digitalWrite(trig2Pin, HIGH);

    delayMicroseconds(10);                 // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trig1Pin, LOW);
    digitalWrite(trig2Pin, LOW);
    StopFunction();
    //After the echo is ready, the next function for
    //measuring ultrasonic values are ready to run.
    measureAndCalculate();
  }
}
//This function is making the measurements of the distance
//and the steering values for the PIDs.
void measureAndCalculate() {

  delayMicroseconds(800);                  // This delay is here to make sure that the echopin has gone
  // low, before a signal is sent to the platooning car from the leading car.
  // It's unknown why, but there a lot of unrealistic measurements at lower delay.

  unsigned long echo1Start = micros();     //The start values for the variables is defined here.
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
    StopFunction();
    int val1 = digitalRead(echo1Pin);       //Tells if the echopin is high or low.
    int val2 = digitalRead(echo2Pin);

    trigBool1 = true;                       //Boolean that's used with the while loop above.

    if (val1 == 0 && trigBool1 == true && readyBool1 == false) //Here the echopin goes low, and therefore the measurement is done.
    {
      echo1End = micros();
      readyBool1 = true;                    // Makes sure that only one endtime is being measured.
    }

    //The same thing as above, is happening for sensor no. 2.
    if (val2 == 0 && trigBool1 == true && readyBool2 == false)
    {
      echo2End = micros();
      readyBool2 = true;
    }

    if (echo1End != 0 && echo2End != 0) {   //If there has been measured an endtime on both sensors,
      echo1Time = echo1End - echo1Start;    //the the function will measure the distance and direction below.
      echo2Time = echo2End - echo2Start;

      //The distance is measured here.
      distanceReal = (echo1Time * 0.034 + echo2Time * 0.034) / 2;
      //Serial.println(distanceReal);


      //If the distance is between 100 and 10, the code will move on from here.
      //This is to eliminate all the flickering values, that will occur from the ultrasonic sensors.
      if (distanceReal < 100 && distanceReal > 10) {

        motorPID();                         //Calculate the PID output for the motor.
        servoPID();                         //Calculates the PID output for the servo.

        //Puts 4 different measurements into an array and calculates the avarage.
        //Only one measurement is used here, so the servo is going back to idle after.
        float difference = (echo1Time * 0.034 - echo2Time * 0.034);
        //With the difference between the two sensors the array is filled up with 4 values.
        //After that an avarage is calculated which is the direction.

        avarage[aCount] = difference; //Calculates the difference between the two sensors, to make a direction value callede difference.
        aCount++;
        if (aCount == 1) {
          directionReal = (avarage[0] + avarage[1] + avarage[2] + avarage[3]) / 1;
          //Serial.println(directionReal);
          aCount = 0;
        }
      }
      measureStarttime = millis();
      delay(80);
      //Serial.println("Endtid for StartFunction");
      //Serial.println(millis());
      StopFunction();
      break;                           //The while loop stops, because the measurements are done.
    }
  }
}

//This function makes sure all the mesured values, are being used for the motor and the servo.
void motorControl() {
  //Makes sure the DC motor dosn't use a PWM signal under 20, because it's the minimal value for the motor to get running.
//  Serial.println(motorPWMOutput);

  if (motorPWMOutput < 20 || motorPWMOutput > 35) {
    motorPWMOutput = 0;
  }
  //Here the motor is getting the signal, for it to start running.
  analogWrite(motorPWMPin, motorPWMOutput);

  servoVal = map(servoPWMOutput, -20, 25, 95, 125);   //Scales the value for the servo from the value that the PID calculates.
  myservo.write(servoVal);                            //Sets the servo position according to the scaled value.
Serial.println(servoVal);
  //Makes the car stop if no signal is received in 500 ms.
  if (millis() - measureStarttime > 500)
  {
    motorPWMOutput = 0;
    analogWrite(motorPWMPin, 0);
  }
}

