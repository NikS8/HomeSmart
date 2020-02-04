class myServerClass : public HTTPserver {
  virtual void processPathname        (const char * key, const byte flags);
  virtual void processGetArgument     (const char * key, const char * value, const byte flags);

  public:
    void responseRedirect();
    void responseData(String data);
};  // end of myServerClass

myServerClass myServer;

void myServerClass::responseRedirect () {
  // TODO create response about bad endpoint
  println(F("HTTP/1.1 200 OK"));
}

void myServerClass::responseData (String data) {
  if (data.length() == 0) {
    data = createDataString();
  }

  println(F("HTTP/1.1 200 OK"));
  println(F("Content-Type: application/json"));
  print(F("Content-Length: "));
  println(data.length());
  println();
  print(data);
}




void myServerClass::processPathname (const char * key, const byte flags){
  // if / -  response data
  // or ignore it for now
  if (strcmp (key, "/") != 0) {
    responseRedirect();
  }

}

void myServerClass::processGetArgument (const char * key, const char * value, const byte flags) {
  if (strcmp (key, "servo") == 0) {
    // do command

    // response command result
    //byte angle = microservo.read();
    byte angle = 22;
    responseData("Success. New angle: " + angle);
  } else {
    responseData("");
  }
}
