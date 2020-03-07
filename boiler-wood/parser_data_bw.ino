/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            parserDataString
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
String parserDataString()
{
  String resultData;
  
  statePin = digitalRead(targetPin);  //  считываем состояние PINa

  //-------------
  if (ETin.receiveData()) {                         // если пришли данные
    byte id = rxdata.ID; // читаем байт, в нем для кого этот пакет

    if (id == ID) { // и если пакет пришел нам

      if (rxdata.action > 0) {   //  и если команда управления
        targetPin = rxdata.targetPin;
        levelPin = rxdata.levelPin;
        pinMode(targetPin, OUTPUT);

        if (rxdata.levelPin > 0) {   //  то управляем реле

          delay(50);
          //       analogWrite(targetPin, levelPin);
          digitalWrite(targetPin, LOW);   // включаем реле
        }
        else
        {
          digitalWrite(targetPin, HIGH);    // выключаем реле
        }

      }
           createTxData();

           //   включаем передачу данных
      
      Serial.print(" ID = ");
      Serial.print(txdata.ID);                 // и отправляем в Serial
      Serial.print("  ");

      Serial.println();
      delay(10);                                     // небольшая задержка, иначе неуспевает

      digitalWrite(DIR, HIGH);                      // включаем передачу
      delay(50);

      ETout.sendData();                              // отправляем
      delay(50);
      // небольшая задержка, иначе неуспевает
      digitalWrite(DIR, LOW);                       // включаем прием
    }
  }
  //----------


  return;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
