/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
                                                            boiler-reserve.ino
                                        Copyright © 2018-2020, Zigfred & Nik.S
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\                            
  Arduino Pro Mini:
Скетч использует 19706 байт (64%) памяти устройства. Всего доступно 30720 байт.
Глобальные переменные используют 786 байт (38%) динамической памяти.
/*****************************************************************************\
  Сервер boiler-reserve выдает данные:
    аналоговые: 
датчики трансформаторы тока  
датчик давления OPEN-SMART
  	цифровые: 
датчик скорости потока воды YF-B5
датчики температуры DS18B20
/*****************************************************************************/

//  Блок DEVICE  --------------------------------------------------------------
//  Arduino Pro Mini
#define DEVICE_ID "boiler-reserve"
#define VERSION 11

//  Блок libraries  -----------------------------------------------------------
#include <Ethernet2.h>          //  httpServer (40112) pins D10,D11,D12,D13
#include <OneWire.h>            //  DS18B20  pin OneWire D9
#include <DallasTemperature.h>  //  DS18B20
#include <RBD_Timer.h>          //  DS18B20
#include <EmonLib.h>            //  трансформаторы тока pins A1,A2,A3
//                                  flow YF-B5 pin D2

//  Блок settings  ------------------------------------------------------------
#include "boiler_reserve_init.h"

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
  managed_by_http_setup();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            loop
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loop() {
  realTimeService();
  resetChecker();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            info
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\

28.01.2021 v11 Reset: disabled 3min reset; 30days still works
16.01.2021 v10 Добавлен управляющий пин 8 для реле, которое должно включать отопление по http запросу
16.01.2021 v9 Reset added (30days uptime, and 3minutes no requests)
10.01.2020 v8 Переход на блочно-модульное программирование
22.11.2019 v7.0 добавлен датчик OPEN-SMART и подсчет импульсов YF-B5 за 15 сек
13.11.2019 v6.0 переход на статические IP и префикс заменен на "br-"
10.03.2019 v5.0 время работы после включения
09.03.2019 v4.7 новая плата и новые трансформаторы тока (откалиброваны)
22.02.2019 v4.6 dell requestTime
07.02.2019 v4.5 удалено все по логсервису
06.02.2019 v4.4 изменение вывода №№ DS18 и префикс заменен на "bb-"
06.02.2019 v4.3 переменным добавлен префикс "boiler-back-"
04.02.2019 v4.2 добавленa "data"
04.02.2019 v4.1 добавлены ds18 коллектора
04.02.2019 v4.0 добавлена функция freeRam()
03.02.2019 v3.4 преобразование в формат  F("")
19.01.2019 v3.3 нумерация контуров коллектора слева направо  
17.01.2019 v3.2 в именах датчиков температуры последние 2 цифры
16.01.2019 v3.1 обозначены места расположения датчиков температуры
15.01.2019 v3.0 дабавлены данные по температуре коллектора
13.01.2019 v2.2 createDataString в формате json
10.01.2019 v2.1 изменен расчет в YF-B5
03.01.2019 v2.0 dell <ArduinoJson.h>
19.12.2018 v1

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            end
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
