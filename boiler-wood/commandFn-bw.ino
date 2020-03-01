//TODO return command result
void processCommand(const char * key, const char * value) {

byte angle;

  if (strcmp (key, "servo") == 0) {
    if(strcmp (value,"0") == 0) {
      Serial.print("servo8: ");
      Serial.println(value);
    angle = servomotor.read();
      Serial.print("servo11: angle= ");
      Serial.println(angle);
    } else {
      Serial.print("servo14: ");
      Serial.println(value);
    //int someInt = someChar - '0'; // это только от 0 до 9
      //value = atoi(inChar);
        //value = int(inChar);
        //value = (int)inChar;
    int valueInt = atoi(value);
    servomotor.write(valueInt);
      Serial.print("servo22: angle= ");
    angle = servomotor.read();
      Serial.println(angle);
    }
  }
}
