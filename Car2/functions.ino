void findError() {
  int i = 0;


  for (i = 9; i > 0; i--)
    errors[i] = errors[i - 1];
  // load new error into top array spot
  errors[0] = (long)distanceVal - (long)distanceReal;

}


void PIDCal() {
  propVal = 2000;
  intVal = 25;
  derVal = 0;
  divider = 10;

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
  PWMOutput = PIDVal + 127;

}

