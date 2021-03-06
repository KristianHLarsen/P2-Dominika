
void servoControl(int servoVal) {
  //  servoVal = analogRead(A0);

  servoVal = map(servoVal, 0, 1023, 75, 145);     // scale it to use it with the servo (value between 0 and 180)
  //Serial.println("Servo: " + String(servoVal));
  if (servoVal >= 75 && servoVal <= 145)
  {
    myservo.write(servoVal);                  // sets the servo position according to the scaled value
    delay(15);                           // waits for the servo to get there
  }
}


void motorControl(int motorVal, int boost) {
  // motorVal = analogRead(A1);
  motorSpeed = 0;
  //Serial.println("MotorVal: " + String(motorVal));
  //Serial.println("Boost: " + String(boost));
  if (motorVal > 510) {
    digitalWrite(dirpin, LOW);
    motorSpeed = (0.153061 * (motorVal - 510));
    if (motorSpeed < 0)
    {
      motorSpeed = 0;
    }
  }
  else if (motorVal > 490 && motorVal < 510)
  {
    motorSpeed = 0;
  }
  else if (motorVal < 490) {
    digitalWrite(dirpin, HIGH);
    motorSpeed = (0.153061 * (motorVal - 490) * (-1));
    if (motorSpeed < 0)
    {
      motorSpeed = 0;
    }
  }
  //if(motorSpeed >= 0 && motorSpeed <= 255)

  analogWrite(pwmpin, motorSpeed);
 // Serial.println(motorSpeed);

}
