/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            createDataString
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
String createDataString() {
  
  String resultData;
  
  resultData.concat(F("{"));
  resultData.concat(F("\n\"deviceId\":"));
  //  resultData.concat(String(DEVICE_ID));
  resultData.concat(F("\"boiler-down\""));
  resultData.concat(F(","));
  resultData.concat(F("\n\"version\":"));
  resultData.concat((int)VERSION);

  resultData.concat(F(","));
  resultData.concat(F("\n\"data\": {"));

  resultData.concat(F("\n\"bd-trans-1\":"));
  resultData.concat(String(emon1.calcIrms(1480), 1));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-trans-2\":"));
  resultData.concat(String(emon2.calcIrms(1480), 1));
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-trans-3\":"));
  resultData.concat(String(emon3.calcIrms(1480), 1));
  for (uint8_t index = 0; index < ds18DeviceCount; index++)
  {
    DeviceAddress deviceAddress;
    ds18Sensors.getAddress(deviceAddress, index);

    resultData.concat(F(",\n\""));
    for (uint8_t i = 0; i < 8; i++)
    {
      if (deviceAddress[i] < 16)  resultData.concat("0");

      resultData.concat(String(deviceAddress[i], HEX));
    }
    resultData.concat(F("\":"));
    resultData.concat(ds18Sensors.getTempC(deviceAddress));
  }
  resultData.concat(F(","));
  resultData.concat(F("\n\"bd-flow\":"));
  resultData.concat(String(getFlowData()));

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

\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
