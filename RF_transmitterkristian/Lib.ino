void sendForspoergsel() {
  RF.print(request);
  Serial.println("vi sender forspoergsel");
}


Timeout


void modtagBekraeftelse() {
  int input, timeout =0,deltaTime;

  deltaTime=millis();

  while(RF.available() > 0) { //vent på
  timeout = millis();
  
  if (timeout > 50000){
  Serial.println("intet signal");
  }
  
      input = Serial.read();
      if (input == 49){
      Serial.println("Modtaget signal");
      }
  }
}

