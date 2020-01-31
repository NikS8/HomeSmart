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

  resultData.concat(F(",\n\"data\": {"));

  for (uint8_t index = 0; index < ds18DeviceCount; index++)
  {
    DeviceAddress deviceAddress;
    ds18Sensors.getAddress(deviceAddress, index);
    resultData.concat(F("\n\t\""));
    for (uint8_t i = 0; i < 8; i++)
    {
      if (deviceAddress[i] < 16) resultData.concat("0");
      resultData.concat(String(deviceAddress[i], HEX));
    }
    resultData.concat(F("\":"));
    resultData.concat(ds18Sensors.getTempC(deviceAddress));
    resultData.concat(F(","));
  }
  resultData.concat(F("\n\t\"cf-hall-f\":"));
  resultData.concat(getFlowDataA3());
  resultData.concat(F(",\n\t\"cf-tv-f\":"));
  resultData.concat(getFlowDataA2());
  resultData.concat(F(",\n\t\"cf-bed-f\":"));
  resultData.concat(getFlowDataA1());
  resultData.concat(F(",\n\t\"cf-st-f\":"));
  resultData.concat(getFlowDataA0());
  resultData.concat(F(",\n\t\"cf-kitch-f\":"));
  resultData.concat(getFlowData2());
  // resultData.concat(F(",\n\t\"cf-radiator-f\":"));
  // resultData.concat(getFlowData3()); //  резерв для 8-й ветки
  resultData.concat(F(",\n\t\"cf-vbath-f\":"));
  resultData.concat(getFlowDataA5());
  resultData.concat(F(",\n\t\"cf-vbed-f\":"));
  resultData.concat(getFlowDataA4());
  resultData.concat(F(",\n\t\"cf-mixer-servo\":"));
  resultData.concat(servo996r.read());
  resultData.concat(F("\n\t }"));
  resultData.concat(F(",\n\"freeRam\":"));
  resultData.concat(freeRam());
  resultData.concat(F(",\n\"upTime\":\""));
  resultData.concat(upTime(millis()));
  resultData.concat(F("\"\n }"));

  return resultData;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/