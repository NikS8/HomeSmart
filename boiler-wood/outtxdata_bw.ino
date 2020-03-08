/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            outTxData
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void outTxData()
{

  
     mySerial.print("bw_pressure = ");
     mySerial.println(getPressureData());    // давление от датчика давления в трубе от бака

      mySerial.print("bw_tPT100_smoke = ");
      mySerial.println(getPT100Data());     //  эл.ток от тр-ра тока ТЭНа №1
 
      mySerial.print("bw_flow = ");
      mySerial.println(getFlowData());     //  эл.ток от тр-ра тока ТЭНа №2
 
      mySerial.print("bw_gy_shutter = ");
      mySerial.println(getGY521Data());     //  эл.ток от тр-ра тока ТЭНа №3
     
      mySerial.print("bw_servo_shutter = ");
      mySerial.println(servomotor.read() - 93);       // температура от датчика DS18B20 на выходном патрубке котла
 
      mySerial.print("bw_dsBoiler = ");
      mySerial.println(ds18Sensors.getTempCByIndex(0));    // температура от датчика DS18B20 на выходном патрубке котла
      mySerial.print("bw_dsBoilerIn = ");
      mySerial.println(ds18Sensors.getTempCByIndex(1));    // температура от датчика DS18B20 на трубе в бак
      mySerial.print("bw_dsBoilerOut = ");
      mySerial.println(ds18Sensors.getTempCByIndex(2));   // температура от датчика DS18B20 на трубе из бака
 
      
  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
