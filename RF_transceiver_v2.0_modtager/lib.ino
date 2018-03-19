
void servoControl(int servoVal) {
//  servoVal = analogRead(A0);
  
  servoVal = map(servoVal, 0, 1023, 75, 145);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(servoVal);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}


void motorControl(int motorVal) {
 // motorVal = analogRead(A1);

  if (motorVal > 510) {
    digitalWrite(dirpin, LOW);
    motorSpeed = (0.13199 * (motorVal - 510));
    if (motorSpeed < 0) {
      motorSpeed = 0;
    }
  }
if(motorVal > 490 && motorVal < 510)
{
  motorSpeed = 0;
}
  if (motorVal < 490) {
    digitalWrite(dirpin, HIGH);
    motorSpeed = (0.133061 * (motorVal - 490) * (-1));
    if (motorSpeed < 0) {
      motorSpeed = 0;
    }
  }

  analogWrite(pwmpin, motorSpeed);
<<<<<<< HEAD
}
=======
}
>>>>>>> 1bb0914d32695a11c22f80f698a40253e73621d1
