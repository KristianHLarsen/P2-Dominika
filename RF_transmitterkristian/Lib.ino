void sendForspoergsel() {
  RF.print(request);
  Serial.print("vi sender forspoergsel");
}

void modtagBekraeftelse() {
  int input, timeout =0;
  timeout = millis();
  
  while(RF.available() == 0) { //vent på
  timeout = millis();
  if (timeout > 5000){
  Serial.println("intet signal");
  }
      input = Serial.read();
      if (input = 49){
      Serial.println("Modtaget signal");
      }
  }
}

