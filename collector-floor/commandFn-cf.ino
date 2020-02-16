//TODO return command result
void processCommand(const char * key, const char * value) {


  if (strcmp (key, "servo") == 0) {
    // do command

  Serial.print("servo29: ");
  Serial.println(value);
    // response command result
    //byte angle = microservo.read();
    //byte angle = 22;
  } else {
  Serial.print("36no servo: ");
  Serial.print(key);
  Serial.print(" ");
  Serial.println(value);
  }
}
