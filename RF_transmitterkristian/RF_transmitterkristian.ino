/* ARDUINO serial RF
 *  
 */

#define request 1

#define 


#include <SoftwareSerial.h>



SoftwareSerial RF(8,9) // RX , TX
void setup()
{
  Serial.begin(9600);
  //Serial.print("WR_433920_3_9_0_0");
  Serial.flush();
  RF.begin(9600);
  
}

void loop()
{
 // Sendforesprøgsel
 // Sodtag bekræftigelse
 //  

 sendForspoergsel();

 modtagBekraeftelse();
  //delay(1000);
}
