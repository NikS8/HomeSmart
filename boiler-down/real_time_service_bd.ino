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
    Serial.println(freeRam());

  if (readString.indexOf("ping") >= 0) {
    data = "PONG";
  } else if (readString.indexOf("command") >= 0) {
    bool runHeater = readString.indexOf("run") >= 0;

    // command?run-h1-h2-h3-h4-h5-h6
    if (runHeater) {
      digitalWrite(heaterStatePins[0], LOW);
    } else {
      digitalWrite(heaterStatePins[0], HIGH);
    }


      if (readString.indexOf("h1") >= 0 && runHeater) {
        digitalWrite(heaterStatePins[1], LOW);
      } else {
        digitalWrite(heaterStatePins[1], HIGH);
      }
      if (readString.indexOf("h2") >= 0 && runHeater) {
        digitalWrite(heaterStatePins[2], LOW);
      } else {
        digitalWrite(heaterStatePins[2], HIGH);
      }
      if (readString.indexOf("h3") >= 0 && runHeater) {
        digitalWrite(heaterStatePins[3], LOW);
      } else {
        digitalWrite(heaterStatePins[3], HIGH);
      }
      if (readString.indexOf("h4") >= 0 && runHeater) {
        digitalWrite(heaterStatePins[4], LOW);
      } else {
        digitalWrite(heaterStatePins[4], HIGH);
      }
      if (readString.indexOf("h5") >= 0 && runHeater) {
        digitalWrite(heaterStatePins[5], LOW);
      } else {
        digitalWrite(heaterStatePins[5], HIGH);
      }
      if (readString.indexOf("h6") >= 0 && runHeater) {
        digitalWrite(heaterStatePins[6], LOW);
      } else {
        digitalWrite(heaterStatePins[6], HIGH);
      }

    //data = commandFn(readString);
    //commandFn(readString);
  } else {
    ds18RequestTemperatures();
    data = createDataString();
  }
    Serial.println(freeRam());

  reqClient.println(F("HTTP/1.1 200 OK"));
  reqClient.println(F("Content-Type: application/json"));
  reqClient.print(F("Content-Length: "));
  reqClient.println(data.length());
  reqClient.println();
  reqClient.print(data);

  reqClient.stop();
      Serial.println(freeRam());

}


//String commandFn(String &readString) {
String commandFn(String &readString) {
  //void result = "Skipped";

  if (readString.indexOf("state") >= 0) {
    //result = "Set: ";
    String parsedStateParam = parseGetParam(readString, "state");

    Serial.println(parsedStateParam);
    Serial.println(freeRam());

    char valueChar[parsedStateParam.length()];
    //parsedStateParam.toCharArray(valueChar, parsedStateParam.length() + 1);
    parsedStateParam.toCharArray(valueChar, parsedStateParam.length());

    Serial.println(freeRam());
    for (int i = 0; i < (sizeof(heaterStatePins) / sizeof(heaterStatePins[0])); i++) {
      //result.concat(i);
      Serial.print(i);
      if (readString.length() > i && char2int(valueChar[i]) == 1 && char2int(valueChar[0]) == 1) {
        //result.concat("-on. ");
        Serial.println("-low - on");
        digitalWrite(heaterStatePins[i], LOW);
      } else {
        //result.concat("-off. ");
        digitalWrite(heaterStatePins[i], HIGH);
        Serial.println("-high - off");
      }
    Serial.println(freeRam());
      delay(20);
    }
    Serial.println(freeRam());
  }

  //return result;
}



int char2int(char c) {
  return c - '0';
}

String parseGetParam(String reqString, String paramName) {
  paramName.concat("=");
  int tmpPos = reqString.indexOf(paramName);
  tmpPos += paramName.length();
  reqString = reqString.substring(tmpPos, reqString.length());

  tmpPos = reqString.indexOf(" ");
  reqString = reqString.substring(0, tmpPos);

  tmpPos = reqString.indexOf("&");
  reqString = reqString.substring(0, tmpPos);

  return reqString;
}



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
