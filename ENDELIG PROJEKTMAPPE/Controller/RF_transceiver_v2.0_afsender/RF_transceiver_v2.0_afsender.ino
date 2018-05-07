#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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


//String        tal = String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '/';
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
  pinMode(carStop, INPUT_PULLUP); //pin for stopping the car
  pinMode(normal, INPUT_PULLUP);  //pin is high for normal operation of car.
}

void lcdPrint()  {
  if (digitalRead(normal) == HIGH) {
    if (analogRead(A1) > 510) {
      motorSpeed = (0.153061 * (analogRead(A1) - 510));
    }
    if (analogRead(A1) > 490 && analogRead(A1) < 510)
    {
      motorSpeed = 0;
    }

    if (analogRead(A1) < 490)  {
      motorSpeed = (0.146199 * (analogRead(A1) - 490) * (-1));
    }
    lcd.setCursor(12, 0);
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

void carStopFunc()  { //Function for when the car is stoppen.
  if (digitalRead(carStop) == HIGH) { //If carStop pin is HIGH
    lcd.setCursor(0, 0);    //Print "EMERGENCY STOP"
    lcd.print("EMERGENCY      ");
    lcd.setCursor(0, 1);
    lcd.print("STOP           ");

    outString[2] = 0; //Emergency "channel". outString[0] and outString[1] is servo and speed.
    String tal = String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '/';
    Serial3.print(tal);    // sender det der blev skrevet i serial monitor over RF
    Serial3.flush();
    Serial.println(tal);
    delay(10);
  }
}

void transmit() {
  if  (digitalRead(normal) == HIGH) {

    outString[0] = analogRead(1);
    outString[1] = analogRead(0);
    outString[2] = 1; //when 0 is sent, car stops. When 1 is sent, car is in normal operation. 

    String tal = String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '!' + '/';
    Serial3.print(tal);    // sender det der blev skrevet i serial monitor over RF
    Serial3.flush();
    Serial.println(tal);
    delay(10);
  }
}

void WaitTransmit() {
  int starttime = millis();
  int endtime = starttime;
  while ((endtime - starttime) <= 120) // do this loop for up to 1000mS
  {
    transmit();
    endtime = millis();
  }
}

void receive()
{
  if (Serial3.available() > 0) {
  }
  inputRF = Serial3.read();   //Serial 3 er koblet til RF modul
  Serial.write(inputRF);      //Skriver til Serial monitor
  Serial.println();
  Serial.println("Modtaget data");
}

void loop()
{
  WaitTransmit();
  lcdPrint();
  carStopFunc();
}

/*
  void receiveString() {

  if (Serial3.available() > 0)
  {
    int modtaget;
    Serial.println("Indtast en streng og slut med !");
    modtaget = Serial3.readBytesUntil(10, inString, INCHAR); //break karakter til
    Serial3.flush();
    Serial.print("modtaget antal:  "); Serial.println(modtaget);
    printString(inString); //som er &(instring[0]) = inString
  }
  }
  void splitUp()
  {
  int seperatorEt = tal.indexOf('!');
  int seperatorTo = tal.indexOf('!', seperatorEt + 1);
  int seperatorTre = tal.indexOf('/');
  String sub1 = tal.substring(0, seperatorEt);
  String sub2 = tal.substring(seperatorEt + 1, seperatorTo);
  String sub3 = tal.substring(seperatorTo + 1, seperatorTre);

  Serial.println(sub1);
  Serial.println(sub2);
  Serial.println(sub3);
  }
*/
