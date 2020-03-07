/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            createTxData
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
String createTxData()
{
  String resultTxData;
  
     ID = 11;
      txdata.ID = ID;

      txdata.bw_pressure = getPressureData();    // давление от датчика давления в трубе от бака

      txdata.bw_tPT100_smoke = getPT100Data();     //  эл.ток от тр-ра тока ТЭНа №1
 
      txdata.bw_flow = getFlowData();     //  эл.ток от тр-ра тока ТЭНа №2
 
      txdata.bw_gy_shutter = getGY521Data();     //  эл.ток от тр-ра тока ТЭНа №3
     
      txdata.bw_servo_shutter = servomotor.read() - 93;       // температура от датчика DS18B20 на выходном патрубке котла
 
      txdata.bw_dsBoiler = ds18Sensors.getTempCByIndex(0);    // температура от датчика DS18B20 на выходном патрубке котла
      txdata.bw_dsBoilerIn = ds18Sensors.getTempCByIndex(1);    // температура от датчика DS18B20 на трубе в бак
      txdata.bw_dsBoilerOut = ds18Sensors.getTempCByIndex(2);   // температура от датчика DS18B20 на трубе из бака
 
      txdata.statePin = statePin;     //  состояние PINa

      //////

    
  return resultTxData;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
