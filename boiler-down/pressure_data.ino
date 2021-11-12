/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            function to measurement pressure
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float getPressureData() {

  unsigned int avg_sum=0;
  for(byte i=0; i<8; i++){
    avg_sum += analogRead(PIN_SENSOR_PRESSURE);
  }
  float press_avg = avg_sum / 8;
 // перевод значений в атм [(sensorPressTankFrom - 0,1*1023) / (1,6*1023/9,8)]
  float pressure = (( press_avg - 102.3) / 167);
  Serial.print(F("   sensorPress = "));
//  Serial.println(pressure);

  return pressure;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
