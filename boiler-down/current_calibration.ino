/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            function getCurrentCalibration
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void getCurrentCalibration(){

 Serial.print("Custom Address:");
    Serial.println(pzem.readAddress(), HEX);

    // Read the data from the sensor
    float voltage = pzem.voltage();
    float current = pzem.current();
    // Check if the data is valid
    if(isnan(voltage)){
        Serial.println("Error reading voltage");
    } else if (isnan(current)) {
        Serial.println("Error reading current");
     } else {
        // Print the values to the Serial console
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
    }

float current_1 = emon1.calcIrms(1480);
float current_2 = emon2.calcIrms(1480);
float current_3 = emon3.calcIrms(1480);
float current_4 = emon4.calcIrms(1480);
float current_5 = emon5.calcIrms(1480);
float current_6 = emon6.calcIrms(1480);
float current_7 = emon7.calcIrms(1480);

current_koef1 = current / current_1;
current_koef2 = current / current_2;
current_koef3 = current / current_3;
current_koef4 = current / current_4;
current_koef5 = current / current_5;
current_koef6 = current / current_6;
current_koef7 = current / current_7;

Serial.println("   Результаты калиброки: "); 
Serial.println(""); 

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

Serial.println(""); 
Serial.println(" Результаты калиброки надо скопировать и заменить"); 
Serial.println(" в файле boiler_down_init.h в Блоке Energy Monitor"); 
Serial.println(""); 
Serial.println("   П а у з а      на   2 минуты"); 
delay(111111);
Serial.println("     Пауза закончилась"); 

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            end
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/