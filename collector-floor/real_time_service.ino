/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            realTimeService
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void realTimeService() {
String readString;

  EthernetClient reqClient = httpServer.available();
  if (!reqClient) return;

  while (reqClient.connected()) {
    if (reqClient.available()) {

      char c = reqClient.read();

      readString += c;


      if (c == '\n') {
        // log it in serial pls:
        Serial.println("readString20");
        Serial.println(readString);

        parseRequest(readString);
        responseData(reqClient);
      }
    }
  }
}

void parseRequest(String &readString) {

  // GET / HTTP1.1
  Serial.print("readString33: ");
  Serial.println(readString);

  MatchState ms;
  //ms.Target("POST / HTTP1");
  ms.Target(readString);

  char buff [100];
  char result = ms.Match("POST (%a) ", 0);
  if (result == REGEXP_MATCHED) {
    Serial.println("matched");
    Serial.println(ms.GetCapture(buff, 0));
  } else if (result == REGEXP_NOMATCH) {
    Serial.println("no match");
  } else {
    Serial.println("FAIL");
  }
}

void responseData(EthernetClient &reqClient) {
  String data = createDataString();

  reqClient.println(F("HTTP/1.1 200 OK"));
  reqClient.println(F("Content-Type: application/json"));
  reqClient.print(F("Content-Length: "));
  reqClient.println(data.length());
  reqClient.println();
  reqClient.print(data);

  reqClient.stop();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/