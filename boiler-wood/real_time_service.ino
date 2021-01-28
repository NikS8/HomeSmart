/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            realTimeService
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void realTimeService() {

  EthernetClient reqClient = httpServer.available();
  if (!reqClient) return;

  String data = "";
  String readString = String(100);

  while (reqClient.available()) {
    char c = reqClient.read();
    if (readString.length() < 100) {
      readString.concat(c);
    }
  }

  if(readString.indexOf("command") >= 0) {
    data = commandFn(readString);
  } else {
    ds18RequestTemperatures();
    data = createDataString();
  }

  reqClient.println(F("HTTP/1.1 200 OK"));
  reqClient.println(F("Content-Type: application/json"));
  reqClient.print(F("Content-Length: "));
  reqClient.println(data.length());
  reqClient.println();
  reqClient.print(data);

  reqClient.stop();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/