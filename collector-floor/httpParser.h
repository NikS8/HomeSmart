class myServerClass : public HTTPserver {
  virtual void processPathname        (const char * key, const byte flags);
  virtual void processGetArgument     (const char * key, const char * value, const byte flags);
  private:
    byte isCommandRequest = false;
    byte isDataRequest = false;
    void responseData() {
      String const data = dataFn();
      println(F("HTTP/1.1 200 OK"));
      println(F("Content-Type: application/json"));
      print(F("Content-Length: "));
      println(data.length());
      println();
      print(data);
    }
    void response() {
      if (isDataRequest) {
        responseData();
      }
      if (isCommandRequest) {
        Serial.println("is command");
        println(F("HTTP/1.1 200 OK"));
        //TODO respond command result
      }
      if (!isDataRequest && !isCommandRequest) {
        Serial.println("no path");
        println(F("HTTP/1.1 404 Not Found"));
        //println(F("HTTP/1.1 301 OK"));
        //println(F("Location: /"));
      }
    }
    void reset() {
      //TODO check if data string should be cleared
      isCommandRequest = false;
      isDataRequest = false;
    }
  public:
    EthernetServer * httpServer;
    String (*dataFn)();
    //int (*freeRam)(); // for debug
    void (*commandFn)(const char * key, const char * value);
    void iterate() {
      EthernetClient reqClient = httpServer->available();
      if (!reqClient) return;

      begin(&reqClient);

      while (reqClient.connected() && !done) {
        while (reqClient.available() > 0 && !done) {
          processIncomingByte (reqClient.read ());
        }
      }

      response();
      flush();
      delay(1);
      reqClient.stop();
      reset();
    }

};  // end of myServerClass

myServerClass myServer;

void myServerClass::processPathname(const char * key, const byte flags){
  Serial.print("path: ");
  Serial.println(key);
  
  if (strcmp (key, "/") == 0) {
    isDataRequest = true;
  }
  if (strcmp (key, "/command") == 0) {
    isCommandRequest = true;
  }
}

void myServerClass::processGetArgument(const char * key, const char * value, const byte flags) {
  // for testing commands
  //Serial.print("processGetArg: " + key + "=" + value);
  if (!isCommandRequest || key == "") {
    return;
  }
  commandFn(key, value);
}
