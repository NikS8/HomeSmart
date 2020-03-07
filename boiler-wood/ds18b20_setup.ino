/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup Ds18Sensors
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ds18b20Setup() {
            
  ds18Sensors.begin();
  ds18DeviceCount = ds18Sensors.getDeviceCount();
  int tempDeviceAddress; 
  ds18Sensors.requestTemperatures();
  ds18ConversionTimer.setTimeout(DS18_CONVERSION_TIME);
  ds18ConversionTimer.restart();

  for(int i=0;i<ds18DeviceCount; i++)
  {
    // Search the wire for address
    if(ds18Sensors.getAddress(tempDeviceAddress, i))
	{
		Serial.print("Found device ");
		Serial.print(i, DEC);
		Serial.print(" with address: ");
	//	printAddress(tempDeviceAddress);
		
		if(i=0) {bw_dsBoilerN = tempDeviceAddress; }

		if(i=1) {bw_dsBoilerInN = tempDeviceAddress;	}

		if(i=2) {bw_dsBoilerOutN = tempDeviceAddress;	}

		Serial.println();
		
		
	}else{
		Serial.print("Found ghost device at ");
		Serial.print(i, DEC);
		Serial.print(" but could not detect address. Check power and cabling");
	}
  }

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
