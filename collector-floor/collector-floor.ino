/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
                                                           collector-floor.ino
                                        Copyright © 2019-2020, Zigfred & Nik.S
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
  Arduino ATmega328 Nano:
Скетч использует 20508 байт (66%) памяти устройства. Всего доступно 30720 байт.
Глобальные переменные используют 638 байт (31%) динамической памяти, 
оставляя 1410 байт для локальных переменных. Максимум: 2048 байт.
/*****************************************************************************\
Сервер collector-floor выдает данные:
  цифровые:
датчики скорости потока воды YF-B5
датчики температуры DS18B20 
датчик положения термоклапана от Servo996R
/*****************************************************************************/

//  Блок DEVICE  --------------------------------------------------------------
//  Arduino ATmega328 Nano
#define DEVICE_ID "collector-floor"
#define VERSION 6

//  Блок libraries  -----------------------------------------------------------
#include <Ethernet2.h>            //  httpServer (40113) pins D10,D11,D12,D13
#include <OneWire.h>              //  DS18B20  pin OneWire D9
#include <DallasTemperature.h>    //  DS18B20  pin OneWire D9
#include <RBD_Timer.h>            //  DS18B20  pin OneWire D9
#include <EnableInterrupt.h>      //  flow YF-B5 pins A0,A1,A2,A3,A4,A5,D2,D3
#include <Servo.h>                //  Servo996R pin 5
#include <HTTPserver.h>

//  Блок settings  ------------------------------------------------------------
#include "collector_floor_init.h"
#include "httpParser.h"

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
  servo996rSetup();

  myServer.httpServer = &httpServer;
  myServer.dataFn = &createDataString;
  myServer.commandFn = &processCommand;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            loop
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loop() {

  ds18RequestTemperatures();

  myServer.iterate();
  
  resetWhen30Days();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            info
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\

31.01.2020 v6 add servo996r
07.01.2020 v5.0 Переход на блочно-модульное программирование
13.12.2019 v4.1 учет импульсов YF-B5 за каждые 15 сек
13.11.2019 v4.0 переход на статические IP
04.03.2019 v3.0 время работы
28.02.2019 v2.1 переименование на collector, cf-hall-f, cf-hall-t ...
27.02.2019 V2.0 add enableInterrupt(2,flowSensorPulseCounter2,FALLING)
26.02.2019 V1.4 коллектор теплого пола:cf-cook,-office,-dorm,-corridor
26.02.2019 V1.3 замена на #include <EnableInterrupt.h>
25.02.2019 V1.2 dell PCINT0_vect, PCINT1_vect и PCINT2_vect
18.02.2019 V1.1 Прерывания PCINT0_vect, PCINT1_vect и PCINT2_vect
31.01.2019 v1

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            end
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
