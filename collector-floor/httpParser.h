class myServerClass : public HTTPserver {
  virtual void processPathname        (const char * key, const byte flags);
  virtual void processGetArgument     (const char * key, const char * value, const byte flags);

  public:
    void responseRedirect();
    void responseData(String data);

};  // end of myServerClass

  myServerClass myServer; 


void myServerClass::processPathname(const char * key, const byte flags){
  // if / -  response data
  // or ignore it for now
  Serial.print("path: ");
  Serial.println(key);
  if (strcmp (key, "/") != 0) {
    responseRedirect();
  }

}

void myServerClass::processGetArgument(const char * key, const char * value, const byte flags) {
  if (strcmp (key, "servo") == 0) {
    // do command

  Serial.print("servo29: ");
  Serial.println(value);
    // response command result
    //byte angle = microservo.read();
    byte angle = 22;
    responseData("Success. New angle: " + angle);
  } else {
  Serial.print("36no servo: ");
  Serial.print(key);
  Serial.print(" ");
  Serial.println(value);
    responseData("test2");
  }
}

void myServerClass::responseRedirect() {
  // TODO create response about bad endpoint
  println(F("HTTP/1.1 200 OK"));
}

void myServerClass::responseData(String data) {
  if (data.length() == 0) {
    //data = createDataString();
    //data = "test data";
  }
Serial.print("in responseData: ");
Serial.println(data);
  println(F("HTTP/1.1 200 OK"));
  println(F("Content-Type: application/json"));
  print(F("Content-Length: "));
  println(data.length());
  println();
  print(data);
}