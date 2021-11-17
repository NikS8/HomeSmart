/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            function to measurement pressure
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float getPressureData() {

  unsigned int avg_sum=0;
  for(byte i=0; i<8; i++){
    avg_sum += analogRead(PIN_PRESSURE_SENSOR);
  }
  float aA0 = avg_sum / 8;
 // перевод значений в атм [(sensorPressTankFrom - 0,1*1023) / (1,6*1023/9,8)]
  float pressure = ((aA0 - 102.3) / 167);
  //  sensorPressTankFrom = (sensorPressTankFrom * 0.0048875);    
  //  Напряжение в вольтах 0-5В
  //  sensorPressTankFrom = (sensorPressTankFrom * 0.0259);
  Serial.print(F("   sensorPress = "));
  Serial.println(pressure);

  return pressure;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
