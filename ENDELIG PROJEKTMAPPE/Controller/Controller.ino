#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*
   This program runs on the controller.
   It transers the analog values from the joysticks with the RF module, and prints it to the LCD as well.
   If the stopbutton is pressed, 0 is sent as the DC-Motor value, so that the cars stop.
*/

//MEGA
int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define INCHAR 100
#define OUTCHAR 100
char inString[INCHAR];
int carStop = 12;
int normal = 13;
int motorSpeed;
int outString[3];

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(30000);
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(30000);
  Serial.flush();
  lcd.begin();
  pinMode(carStop, INPUT_PULLUP);    //pin for stopping the car
  pinMode(normal, INPUT_PULLUP);     //pin is high for normal operation of car.
}

void lcdPrint()  {
  if (digitalRead(normal) == HIGH) {
    if (analogRead(A1) > 510) {
      motorSpeed = (0.153061 * (analogRead(A1) - 510));   // Conversion model between analog values (0-1023) and PWM (0-255) forward. 
    }
    if (analogRead(A1) > 490 && analogRead(A1) < 510)     // If the joysticks are centered (not in use), do nothing
    {
      motorSpeed = 0;
    }

    if (analogRead(A1) < 490)  {                         // Conversion model between analog values (0-1023) and PWM (0-255) backward. 
      motorSpeed = (0.146199 * (analogRead(A1) - 490) * (-1));
    }
    lcd.setCursor(12, 0);                                // Printing values to the LCD
    lcd.print("    ");
    lcd.setCursor(12, 1);
    lcd.print("    ");
    lcd.setCursor(0, 0);
    lcd.print("Servo value ");
    lcd.print(analogRead(A0));
    lcd.setCursor(0, 1);
    lcd.print("Motor speed ");
    lcd.print(outString[0]);
  }
}

void carStopFunc()  {                       //Function for when the car is stopped.
  if (digitalRead(carStop) == HIGH) {       //If carStop pin is HIGH
    lcd.setCursor(0, 0);                    //Print "EMERGENCY STOP" to the LCD. 
    lcd.print("EMERGENCY      ");
    lcd.setCursor(0, 1);
    lcd.print("STOP           ");

    outString[2] = 0;                       // Emergency "channel". outString[0] and outString[1] is servo and speed.
    String tal = '=' + String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '/';
    Serial3.print(tal);                     // Sends the number with RF
    Serial3.flush();
    delay(10);
  }
}

void transmit() {
  if  (digitalRead(normal) == HIGH) {       // Normal operation
    outString[0] = analogRead(1);           // Joystick for steering
    outString[1] = analogRead(0);           // Joystick for speed
    outString[2] = 1;                       // when 0 is sent, car stops. When 1 is sent, car is in normal operation.

    String tal = '=' + String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '!' + '/';
    Serial3.print(tal);                     // Sending what was written to the serial monitor by RF.
    Serial3.flush();
    delay(10);
  }
}

void WaitTransmit() {
  unsigned long starttime = millis();
  unsigned long endtime = starttime;
  while ((endtime - starttime) <= 120) //Do this loop for up to 1000mS
  {
    transmit();
    endtime = millis();
    delay(100);
  }
}

void receive()
{
  if (Serial3.available() > 0) {
  }
  inputRF = Serial3.read();   //Serial 3 is connected to RF module.
  Serial.write(inputRF);      //Writing to serial monitor.
  Serial.println();
  Serial.println("Modtaget data");
}

void loop()
{
  WaitTransmit();
  lcdPrint();
  carStopFunc();
}
