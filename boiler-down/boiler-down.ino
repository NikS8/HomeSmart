/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
                                                               boiler-down.ino
                                        Copyright © 2018-2020, Zigfred & Nik.S
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\                            
  Arduino Pro Mini:
Скетч использует 19736 байт (64%) памяти устройства. Всего доступно 30720 байт.
Глобальные переменные используют 780 байт (38%) динамической памяти.
/*****************************************************************************\
  Сервер boiler-down выдает данные:
    аналоговые: 
датчики трансформаторы тока (pins A1, A2, A3)
    цифровые:
датчик скорости потока воды YF-B5 (D2)(количество импульсов за 15 сек)
датчики температуры DS18B20 (OneWire pin D9)
дальномер HC-SR04 (D1, D3)(измерение уровня воды)
/*****************************************************************************/

//  Блок DEVICE  --------------------------------------------------------------
//  Arduino Pro Mini
#define DEVICE_ID "boiler-down"
#define VERSION 9

//  Блок libraries  -----------------------------------------------------------
#include <Ethernet2.h>          //  httpServer (40102) pins D10,D11,D12,D13
#include <OneWire.h>            //  DS18B20  pin OneWire D9
#include <DallasTemperature.h>  //  DS18B20
#include <RBD_Timer.h>          //  DS18B20
#include <EmonLib.h>            //  трансформаторы тока pins A1,A2,A3
//                                  flow YF-B5 pin D2

//  Блок settings  ------------------------------------------------------------
#include "boiler_down_init.h"

//	end init  -----------------------------------------------------------------

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void setup() {

  Serial.begin(9600);
  Serial.println("Serial.begin(9600)"); 
  
  Serial.print(F("FREE RAM: "));
  Serial.println(freeRam());
  
  httpServerSetup();
  ds18b20Setup();
  yfb5InterruptSetup();
  currentSetup();
  relayModuleSetup();
  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            loop
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
byte incomingByte;
//bool reseted = false;
void loop() {
  realTimeService();
  resetChecker();
  serialLoop();

}

void serialLoop() {
  
  if (Serial.available() > 0) {

    
    // read the incoming byte:
    incomingByte = Serial.read();

    if (millis() < 20000) {
      return;
    }
    // enable all heaters by send "1" to serial
    // disable by any other char
    //Serial.println(incomingByte);
    if (incomingByte == 49) {
      for (int i = 0; i < (sizeof(heaterStatePins) / sizeof(heaterStatePins[0])); i++) {
        digitalWrite(heaterStatePins[i], LOW);
      }
      Serial.println("ON");
      return;
    }
    if (incomingByte == 48) {
      for (int i = 0; i < (sizeof(heaterStatePins) / sizeof(heaterStatePins[0])); i++) {
        digitalWrite(heaterStatePins[i], HIGH);
      }
      Serial.println("OFF");
      return;
    }

    if (incomingByte == 50) {
      Serial.println("DS18 data:");
      for (uint8_t index = 0; index < ds18DeviceCount; index++) {
        DeviceAddress deviceAddress;
        ds18Sensors.getAddress(deviceAddress, index);
    
        for (uint8_t i = 0; i < 8; i++) {
          if (deviceAddress[i] < 16)  {
            // ??
          }
          Serial.print(String(deviceAddress[i], HEX));
        }
        Serial.print(": ");
        Serial.println(ds18Sensors.getTempC(deviceAddress));
      }
      return;
    }

    Serial.println("HELP: 0 - OFF all. 1 - ON all. 2 - print ds18 data");
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            info
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\

28.01.2021 v9 Reset: disabled 3min reset; 30days still works
16.01.2021 v8 Reset added (30days uptime, and 3minutes no requests)
02.01.2020 v7 Переход на блочно-модульное программирование
13.11.2019 v6.0 переход на статические IP
10.02.2019 v5.0 добавлено измерение уровня воды (дальномер HC-SR04)
10.02.2019 v4.2 удален intrevalLogService
06.02.2019 v4.1 изменение вывода №№ DS18 и префикс заменен на "bd-"
04.02.2019 v4.0 добавлена функция freeRam()
04.02.2019 v3.0 структура вывода данных в базу в формате ("data: { }")
04.02.2019 v2.3 переменные с префиксом boiler-down-
03.02.2019 v2.2 преобразование в формат  F("")
28.01.2019 v2.1 переименование boilerDown в boiler-down
23.01.2019 v2.0 добавлены ds18 ТА и в №№ ds18 только 2 знака 
11.01.2019 v1.3 переименование boiler6kw в boilerDown
10.01.2019 v1.2 изменен расчет в YF-B5
03.01.2019 v1.1 откалиброваны коэфициенты трансформаторов тока
31.12.2018 v1

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            end
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
