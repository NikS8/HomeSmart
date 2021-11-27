/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
                                                               boiler-down.ino
                                        Copyright © 2018-2021, Zigfred & Nik.S
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
  Arduino MEGA 2560 PRO:
Sketch uses 27408 bytes (10%) of program storage space. Maximum is 253952 bytes.
Global variables use 1666 bytes (20%) of dynamic memory,
leaving 6526 bytes for local variables. Maximum is 8192 bytes.
/*****************************************************************************\
  Сервер boiler-down выдает данные:
    аналоговые:
датчики трансформаторы тока (pins A0, A1, A2, A3, A4, A5, A6)
    цифровые:
датчик скорости потока воды YF-B5 (D2, D3)(количество импульсов за 15 сек)
датчики температуры DS18B20 (OneWire pin D41, D42, D43)
дальномер HC-SR04 (D22, D23)(измерение уровня воды)
серво для поворота клапана от Servo996R (pins D4,D5)
PZEM004 added to board but not supported yet
    звуковые:
speak pin D46
/*****************************************************************************/

//  Блок DEVICE  --------------------------------------------------------------
//  Arduino MEGA 2560 PRO (ROBODYN)
#define DEVICE_ID "boiler-down"
#define VERSION 10

//  Блок libraries  -----------------------------------------------------------
#include <Ethernet2.h>          //  httpServer (40102) pins D50-D53
#include <OneWire.h>            //  DS18B20 pins OneWire D40, D41, D42, D43
#include <DallasTemperature.h>  //  DS18B20
#include <RBD_Timer.h>          //  DS18B20
#include <EmonLib.h>            //  трансформаторы тока pins A0,A1,A2,A3,A4,A5,A6
#include <hcsr04.h>             //  HC-SR04  pins D22,D23
#include <Servo.h>              //  Servo996R pins D4,D5
//                              //  speaker pin D46

//  Блок settings  ------------------------------------------------------------
#include "boiler_down_init.h"

//	end init  -----------------------------------------------------------------

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void setup() {
  tone(PIN_SPEAKER, 3000, 300);

  Serial.begin(9600);
  Serial.println("Serial.begin(9600)");

  Serial.print(F("FREE RAM: "));
  Serial.println(freeRam());

  ds18b20Setup();
  yfb5InterruptSetup();
  currentSetup();
  servo996rSetup();
  relayModuleSetup();

  httpServerSetup();

    Serial.println("HELP: 0 - OFF all. 1 - ON all. 2 - print ds18 data");
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            loop
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loop() {
  realTimeService();
  resetChecker();
  serialLoop();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            info
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\

24.11.2021 v10 установлен контроллер Mega2560 Pro
28.01.2021 v9.0 Reset: disabled 3min reset; 30days still works
16.01.2021 v8.0 Reset added (30days uptime, and 3minutes no requests)
02.01.2020 v7.0 Переход на блочно-модульное программирование
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
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
