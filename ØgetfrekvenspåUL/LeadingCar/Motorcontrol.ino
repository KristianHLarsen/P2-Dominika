/*
 * This file controls the motors on the car with the data from the controller. 
*/

void servoControl(int servoVal) {
  servoVal = map(servoVal, 0, 1023, 115, 55);    // Servo range: 35-135 
                                                 // The range used is 55-115 for a soft steering without sudden movements.
                                                 // We scale it to use it with the servo (value between 0 and 180)
  myservo.write(servoVal);                       // Sets the servo position according to the scaled value
  delay(15);                                     // Waits for the servo to get there
}


void motorControl(int motorVal) {
  if (motorVal > 510) {                          // If the analog value is above 510 (forward)
    digitalWrite(INa, LOW);
    digitalWrite(INb, HIGH);
    motorSpeed = (0.13199 * (motorVal - 510));   // Conversion between analog values (0-1023) and PWM (0-255) forward-driving
    if (motorSpeed < 0) {
      motorSpeed = 0;
    }
    if (motorSpeed > 30)                         // Limit speed to 30 for easy driving
    {
      motorSpeed = 30;
    }
  }
  if (motorVal > 490 && motorVal < 510)          // If the analog value is between 490 and 510 (when the joysticks are not used)
  {
    motorSpeed = 0;                              // Do nothing
  }
  if (motorVal < 490) {                          // If the analog value is below 490 (backward)
    digitalWrite(INa, HIGH);                     // Change direction on the H-bridge
    digitalWrite(INb, LOW);
    motorSpeed = (0.133061 * (motorVal - 490) * (-1));  // Use another conversion between analog values and PWM. 
    if (motorSpeed < 0) {
      motorSpeed = 0;
    }
    if (motorSpeed > 30)                         // Limit speed to 30. 
    {
      motorSpeed = 30;
    }
  }
  analogWrite(pwmpin, motorSpeed);               // Set the motorspeed. 
}
