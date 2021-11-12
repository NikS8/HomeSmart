/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            function getCurrentCalibration
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float getCurrentCalibration(){

  emon1.current(1, 9.3);
  emon2.current(2, 1);
  emon3.current(3, 1);
  emon4.current(4, 1);
  emon5.current(5, 1);
  emon6.current(6, 1);
  emon7.current(7, 1);
  
float current_etalon = emon1.calcIrms(1480);
float current_2 = emon2.calcIrms(1480);
float current_3 = emon3.calcIrms(1480);
float current_4 = emon4.calcIrms(1480);
float current_5 = emon5.calcIrms(1480);
float current_6 = emon6.calcIrms(1480);
float current_7 = emon7.calcIrms(1480);

current_koef2 = current_etalon / current_2;
current_koef3 = current_etalon / current_3;
current_koef4 = current_etalon / current_4;
current_koef5 = current_etalon / current_5;
current_koef6 = current_etalon / current_6;
current_koef7 = current_etalon / current_7;

Serial.println("   Калиброка виполнена"); 

Serial.print("float current_koef2 = "); Serial.print(current_koef2);  
Serial.println(";"); 
Serial.print("float current_koef3 = "); Serial.print(current_koef3);  
Serial.println(";"); 
Serial.print("float current_koef4 = "); Serial.print(current_koef4);  
Serial.println(";"); 
Serial.print("float current_koef5 = "); Serial.print(current_koef5);  
Serial.println(";"); 
Serial.print("float current_koef6 = "); Serial.print(current_koef6);  
Serial.println(";"); 
Serial.print("float current_koef7 = "); Serial.print(current_koef7);  
Serial.println(";"); 

Serial.println(" Результаты калиброки надо скопировать "); 
Serial.println(" в файл boiler_down_init.h в Блок Energy Monitor"); 

Serial.println("   П а у з а      на   16 минут"); 

delay(999999);

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            end
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/