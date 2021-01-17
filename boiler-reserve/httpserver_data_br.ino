/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            createDataString
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
String createDataString() {
  
  String resultData;

  resultData.concat(F("{"));
  resultData.concat(F("\n\"deviceId\":\""));
  resultData.concat(DEVICE_ID);
  resultData.concat(F("\",\n\"version\":"));
  resultData.concat(VERSION);

  resultData.concat(F(","));
  resultData.concat(F("\n\"data\": {"));

  resultData.concat(F("\n\"br-trans-1\":"));
  resultData.concat(String(emon1.calcIrms(1480), 1));
  resultData.concat(F(","));
  resultData.concat(F("\n\"br-trans-2\":"));
  resultData.concat(String(emon2.calcIrms(1480), 1));
  resultData.concat(F(","));
  resultData.concat(F("\n\"br-trans-3\":"));
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
  resultData.concat(F("\n\"br-flow\":"));
  resultData.concat(String(getFlowData()));

  resultData.concat(F(","));
  resultData.concat(F("\n\"cf-pressure\":"));
  resultData.concat(String(getPressureData(), 2));

  resultData.concat(F(","));
  resultData.concat(F("\n\"br-force-enabled\":"));
  resultData.concat(digitalRead(PIN_MANAGED));

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
