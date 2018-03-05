/*
void fremad(){
setMotorSpeed(leftMotor, 20);
setMotorSpeed(rightMotor, 20);
}
void stopmotoren(){
setMotorSpeed(leftMotor, 0);
setMotorSpeed(rightMotor, 0);
}
void drejHoejre(){
setMotorSpeed(leftMotor, 20);
setMotorSpeed(rightMotor,-20);
}
void drejVenstre(){
setMotorSpeed(leftMotor,-20);
setMotorSpeed(rightMotor,20);
}

task venstreOm()
{
fremad();
waitUntil(getUSDistance(sonarSensor) < 20 );
stopmotoren();
resetGyro(gyroSensor);
drejVenstre();
waitUntil(getGyroDegrees(gyroSensor) > 60);
fremad();
sleep(3000);
stopmotoren();
resetGyro(gyroSensor);
drejHoejre();
waitUntil(getGyroDegrees(gyroSensor) > -60);
fremad();
}*/
