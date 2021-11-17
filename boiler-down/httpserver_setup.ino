/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup httpServer
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void httpServerSetup() {

  Ethernet.init(PIN_CS);
  delay(88);
  Ethernet.begin(mac, ip);
  delay(88);
  Serial.println(F("Server is ready."));
  Serial.print(F("Please connect to http://"));
  Serial.println(Ethernet.localIP());
  delay(88);
  httpServer.begin();
/*
    //  Запрос статуса соединения
  //  Вывод текста в монитор последовательного порта
  Serial.print("Link status: ");
  Serial.println(EthernetServerstatus());
  
  Serial.print("Если Unknown Статус: неизвестно. ");
  Serial.println("Если LinkON подключение есть. Если LinkOFF подключения нет");
*/
 
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/