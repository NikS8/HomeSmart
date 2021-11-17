/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup Ds18Sensors
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ds18b20Setup() {
            
  ds18SensorsBD.begin();
  ds18DeviceCountBD = ds18SensorsBD.getDeviceCount();
  ds18SensorsBD.requestTemperatures();

  ds18SensorsBT.begin();
  ds18DeviceCountBT = ds18SensorsBT.getDeviceCount();
  ds18SensorsBT.requestTemperatures();

  ds18SensorsTA.begin();
  ds18DeviceCountTA = ds18SensorsTA.getDeviceCount();
  ds18SensorsTA.requestTemperatures();

  ds18SensorsHP.begin();
  ds18DeviceCountHP = ds18SensorsHP.getDeviceCount();
  ds18SensorsHP.requestTemperatures();

  ds18ConversionTimer.setTimeout(DS18_CONVERSION_TIME);
  ds18ConversionTimer.restart();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/