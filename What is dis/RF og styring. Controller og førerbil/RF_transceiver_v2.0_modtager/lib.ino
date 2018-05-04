void servoControl(int servoVal) {
  //  servoVal = analogRead(A0);

  servoVal = map(servoVal, 0, 1023, 105, 65);    // Maks 35-135 // scale it to use it with the servo (value between 0 and 180)
  myservo.write(servoVal);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}


void motorControl(int motorVal) {
  // motorVal = analogRead(A1);
  if (motorVal > 510) {
    digitalWrite(INa, LOW);
    digitalWrite(INb, HIGH);
    motorSpeed = (0.06 * (motorVal - 510));
    if (motorSpeed < 0) {
      motorSpeed = 0;
    }
    if (motorSpeed > 30)
    {
      motorSpeed = 30;
    }
  }
  if (motorVal > 490 && motorVal < 510)
  {
    motorSpeed = 0; 
  }
  if (motorVal < 490) {
    digitalWrite(INa, HIGH);
    digitalWrite(INb, LOW);
    motorSpeed = (0.06 * (motorVal - 490) * (-1));
    if (motorSpeed < 0) {
      motorSpeed = 0;
    }
    if (motorSpeed > 30)
    {
      motorSpeed = 30;
    }
  }

  analogWrite(pwmpin, motorSpeed);
  Serial.println(motorSpeed);
}
