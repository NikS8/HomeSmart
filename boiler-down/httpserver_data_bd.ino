/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            createDataString
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
String createDataString() {
  
  String resultData;

    resultData.concat(F("{"));
  resultData.concat(F("\n\"deviceId\":\""));
  resultData.concat(DEVICE_ID);
  //  resultData.concat(F("\"collector\""));
  resultData.concat(F("\",\n\"version\":"));
  resultData.concat(VERSION);
/*
  
  resultData.concat(F("{"));
  resultData.concat(F("\n\"deviceId\":"));
  //  resultData.concat(String(DEVICE_ID));
  resultData.concat(F("\"boiler-down\""));
  resultData.concat(F(","));
  resultData.concat(F("\n\"version\":"));
  resultData.concat((int)VERSION);
*/
  resultData.concat(F(","));
  resultData.concat(F("\n\"data\": {"));
//  трансформаторы тока
  resultData.concat(F("\n\"bd-trans-1\":"));
  resultData.concat(String(emon1.calcIrms(1480), 1));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-trans-2\":"));
  resultData.concat(String(emon2.calcIrms(1480), 1));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-trans-3\":"));
  resultData.concat(String(emon3.calcIrms(1480), 1));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-trans-4\":"));
  resultData.concat(String(emon4.calcIrms(1480), 1));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-trans-5\":"));
  resultData.concat(String(emon5.calcIrms(1480), 1));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-trans-6\":"));
  resultData.concat(String(emon6.calcIrms(1480), 1));
   resultData.concat(F(","));
  resultData.concat(F("\n\"bd-trans-7\":"));
  resultData.concat(String(emon7.calcIrms(1480), 1));
//  ds18b20 
  for (uint8_t index = 0; index < ds18DeviceCountBD; index++)
  {
    DeviceAddress deviceAddress;
        ds18SensorsBD.getAddress(deviceAddress, index);

    resultData.concat(F(",\n\""));
    for (uint8_t i = 0; i < 8; i++)
    {
      if (deviceAddress[i] < 16)  resultData.concat("0");

      resultData.concat(String(deviceAddress[i], HEX));
    }
    resultData.concat(F("\":"));
    resultData.concat(ds18SensorsBD.getTempC(deviceAddress));
  }

 for (uint8_t index = 0; index < ds18DeviceCountBT; index++)
  {
    DeviceAddress deviceAddress;
        ds18SensorsBT.getAddress(deviceAddress, index);

    resultData.concat(F(",\n\""));
    for (uint8_t i = 0; i < 8; i++)
    {
      if (deviceAddress[i] < 16)  resultData.concat("0");

      resultData.concat(String(deviceAddress[i], HEX));
    }
    resultData.concat(F("\":"));
    resultData.concat(ds18SensorsBT.getTempC(deviceAddress));
  }

  for (uint8_t index = 0; index < ds18DeviceCountTA; index++)
  {
    DeviceAddress deviceAddress;
        ds18SensorsTA.getAddress(deviceAddress, index);

    resultData.concat(F(",\n\""));
    for (uint8_t i = 0; i < 8; i++)
    {
      if (deviceAddress[i] < 16)  resultData.concat("0");

      resultData.concat(String(deviceAddress[i], HEX));
    }
    resultData.concat(F("\":"));
    resultData.concat(ds18SensorsTA.getTempC(deviceAddress));
  }

  for (uint8_t index = 0; index < ds18DeviceCountHP; index++)
  {
    DeviceAddress deviceAddress;
        ds18SensorsHP.getAddress(deviceAddress, index);

    resultData.concat(F(",\n\""));
    for (uint8_t i = 0; i < 8; i++)
    {
      if (deviceAddress[i] < 16)  resultData.concat("0");

      resultData.concat(String(deviceAddress[i], HEX));
    }
    resultData.concat(F("\":"));
    resultData.concat(ds18SensorsHP.getTempC(deviceAddress));
  }
//  yf-b5
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-flow-Boiler\":"));
  resultData.concat(String(getFlowDataBoiler()));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-flow-TA\":"));
  resultData.concat(String(getFlowDataTA()));

  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-heater-run\":"));
  resultData.concat(digitalRead(PIN_HEATER_RUN));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-heater-1\":"));
  resultData.concat(digitalRead(PIN_HEATER_1));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-heater-2\":"));
  resultData.concat(digitalRead(PIN_HEATER_2));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-heater-3\":"));
  resultData.concat(digitalRead(PIN_HEATER_3));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-heater-4\":"));
  resultData.concat(digitalRead(PIN_HEATER_4));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-heater-5\":"));
  resultData.concat(digitalRead(PIN_HEATER_5));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-heater-6\":"));
  resultData.concat(digitalRead(PIN_HEATER_6));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-heater-7\":"));
  resultData.concat(digitalRead(PIN_HEATER_7));

  resultData.concat(F(","));
  resultData.concat(F("\n\"ta-level\":"));
  resultData.concat((400 - taLevelWater) / 10.0);
  resultData.concat(F(","));
  resultData.concat(F("\n\"ta-level-filled%\":"));
  resultData.concat((int)((400 - taLevelWater) / 4));

  resultData.concat(F("\n}"));
  resultData.concat(F(","));
  resultData.concat(F("\n\"freeRam\":"));
  resultData.concat(freeRam());
  resultData.concat(F(",\n\"upTime\":\""));
  resultData.concat(upTime(millis()));

  resultData.concat(F("\"\n}"));

  return resultData;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
