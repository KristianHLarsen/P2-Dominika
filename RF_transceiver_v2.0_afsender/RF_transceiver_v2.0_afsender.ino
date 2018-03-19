#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//MEGA
int inputRF; //input Radio Frequency
int inputSM; // input serial monitor
#define NRCHAR 100
#define OUTCHAR 100
char inString[NRCHAR];
int boost = 12;
int normal = 13;
int motorSpeed;

//String        tal = String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '/';
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(30000);
  //Serial.print("WR_433920_3_9_0_0");
  Serial3.begin(9600);
  Serial3.flush();
  Serial3.setTimeout(30000);
  Serial.flush();
  //  splitUp();
  lcd.begin();
  pinMode(boost, INPUT_PULLUP);
  pinMode(normal, INPUT_PULLUP);

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

void lcdPrint()  {
<<<<<<< HEAD
  if (digitalRead(normal) == HIGH) {
    if (analogRead(A1) > 510) {
      motorSpeed = (0.194932 * (analogRead(A1) - 510));
    }
    if (analogRead(A1) > 490 && analogRead(A1) < 510)
    {
      motorSpeed = 0;
    }

    if (analogRead(A1) < 490)  {
      motorSpeed = (0.204082 * (analogRead(A1) - 490) * (-1));
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
    lcd.print(motorSpeed);
=======
  int motorSpeed;
  if (analogRead(A1) > 510) {
    motorSpeed = (0.13199 * (analogRead(A1) - 510));
  }
  if (analogRead(A1) > 490 && analogRead(A1) < 510)
  {
    motorSpeed = 0;
>>>>>>> e4e8ed12ac592f0a403d67dc446a7bf2115fda17
  }

  if (digitalRead(boost) == HIGH) {
    if (analogRead(A1) > 510) {
      motorSpeed = (0.194932 * (analogRead(A1) - 510));
    }
    if (analogRead(A1) > 490 && analogRead(A1) < 510)
    {
      motorSpeed = 0;
    }

    if (analogRead(A1) < 490)  {
      motorSpeed = (0.204082 * (analogRead(A1) - 490) * (-1)*2);
    }

    lcd.setCursor(12, 0);
    lcd.print("    ");
    lcd.setCursor(12, 1);
    lcd.print("    ");
    lcd.setCursor(0, 0);
    lcd.print("Servo value ");
    lcd.print(analogRead(A0));
    lcd.setCursor(0, 1);
    lcd.print("Boost speed ");
    lcd.print(motorSpeed);
  }
}

void loop()
{
  // receiveString();
  WaitTransmit();
  lcdPrint();
}

void receive()
{
  if (Serial3.available() > 0) {
  }
  inputRF = Serial3.read();   //serial 3 er koblet til RF modul
  Serial.write(inputRF);      // skriver til Serial monitor
  Serial.println();
  Serial.println("Modtaget data");
}

void transmit()
{
  int outString[3];
  if  (digitalRead(normal) == HIGH) {

    outString[0] = analogRead(1);
    outString[1] = analogRead(0);
    outString[2] = 1;

    String tal = String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '/';

    //String tal = String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '/';
    Serial3.print(tal);    // sender det der blev skrevet i serial monitor over RF
    Serial3.flush();
    Serial.println(tal);
    delay(10);
  }

  if  (digitalRead(boost) == HIGH) {

    outString[0] = analogRead(1);
    outString[1] = analogRead(0);
    outString[2] = 2.5;

    String tal = String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '/';

    //String tal = String(outString[0]) + '!' + String(outString[1]) + '!' + String(outString[2]) + '/';
    Serial3.print(tal);    // sender det der blev skrevet i serial monitor over RF
    Serial3.flush();
    Serial.println(tal);
    delay(10);
  }
}
/*
  void receiveString() {

  if (Serial3.available() > 0)
  {
    int modtaget;
    Serial.println("Indtast en streng og slut med !");
    modtaget = Serial3.readBytesUntil(10, inString, NRCHAR); //break karakter til
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
<<<<<<< HEAD
*/
=======
<<<<<<< HEAD
*/
=======
*/
>>>>>>> 1bb0914d32695a11c22f80f698a40253e73621d1
>>>>>>> 5d069c3d500bb230ce1924ad4bc631728a6e7ecb
