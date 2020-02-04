/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            realTimeService
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void realTimeService() {
String readString;

  EthernetClient reqClient = httpServer.available();
  if (!reqClient) return;

  myServer.begin(&reqClient);

  while (reqClient.connected() && !myServer.done) {
    while (reqClient.available() > 0 && !myServer.done)
      myServer.processIncomingByte (reqClient.read ());

      //responseData(myServer);


      myServer.flush();
      //delay(1);
      reqClient.stop();
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
