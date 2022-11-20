/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            createDataString
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
String createDataString()
{
  String resultData;
  
  resultData.concat(F("{"));
  resultData.concat(F("\n\"deviceId\":\""));
  resultData.concat(DEVICE_ID);
  resultData.concat(F("\",\n\"version\":"));
  resultData.concat(VERSION);

  resultData.concat(F(","));
  resultData.concat(F("\n\"data\": {"));

  resultData.concat(F("\n\t\"bw-pressure\":"));
  resultData.concat(String(getPressureData(), 2));

  for (uint8_t index = 0; index < ds18DeviceCount; index++)
  {
    DeviceAddress deviceAddress;
    ds18Sensors.getAddress(deviceAddress, index);

    resultData.concat(F(",\n\t\""));
    for (uint8_t i = 0; i < 8; i++)
    {
      if (deviceAddress[i] < 16) resultData.concat("0");

      resultData.concat(String(deviceAddress[i], HEX));
    }
    resultData.concat(F("\":"));
    resultData.concat(ds18Sensors.getTempC(deviceAddress));
  }
  
  resultData.concat(F(",\n\t\"bw-flow\":"));
  resultData.concat(String(getFlowData()));

  resultData.concat(F(",\n\t\"bw-smoke-1\":"));
  resultData.concat(String(thermocouple.readCelsius()));
  
  resultData.concat(F(",\n\t\"bw-shutter-gy\":"));
  resultData.concat(getGY521Data());
  
  resultData.concat(F(",\n\t\"bw-shutter-servo\":"));
  resultData.concat(servomotor.read());
   
  resultData.concat(F("\n\t}"));
 
  resultData.concat(F(",\n\"freeRam\":"));
  resultData.concat(freeRam());
  resultData.concat(F(",\n\"upTime\":\""));
  resultData.concat(upTime(millis()));
  
  resultData.concat(F("\"\n}"));

  return resultData;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
