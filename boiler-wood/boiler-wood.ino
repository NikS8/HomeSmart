/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
                                                               boiler-wood.ino 
                                        Copyright © 2018-2020, Zigfred & Nik.S
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
  Arduino Atmega328 Pro Mini:
Скетч использует 24788 байт (80%) памяти устройства. Всего доступно 30720 байт.
Глобальные переменные используют 985 байт (48%) динамической памяти,
оставляя 1063 байт для локальных переменных. Максимум: 2048 байт.
/*****************************************************************************\
 Сервер boiler-wood выдает данные: 
  аналоговые: 
    датчик давления (A0)
  цифровые: 
    датчик скорости потока воды YF-B5(D2) (количество импульсов за 15 сек)
    датчики температуры DS18B20 (D9)
    датчик угла GY-521 (I2C A4, A5)
    датчик угла от Servo995 (D5)
    датчик температуры (k-type) с платой MAX6675  (D6, D7, D8)
/*****************************************************************************/

//  Блок DEVICE  --------------------------------------------------------------
//  Arduino Atmega328 Pro Mini
#define DEVICE_ID "boiler-wood"
#define VERSION 11

//  Блок libraries  -----------------------------------------------------------
#include <avr/wdt.h>
#include <Ethernet2.h>          //  httpServer (40111) pins D10,D11,D12,D13
#include <OneWire.h>            //  DS18B20  pin OneWire D9
#include <DallasTemperature.h>  //  DS18B20
#include <RBD_Timer.h>          //  DS18B20
#include <max6675.h>            //  MAX6675 thermocouple SPI: D6, D7, D8
#include <I2Cdev.h>             //  GY-521 (I2C A4,A5)
#include <MPU6050.h>            //  GY-521
#include <Servo.h>              //  Servo995 pin 5
                                //  flow YF-B5 pin D2
                                //  speaker pin D3

//  Блок settings  ------------------------------------------------------------
#include "boiler_wood_init.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void setup() {
  wdt_disable();
  addSound(toneStartup);

  Serial.begin(9600);
  Serial.println("Serial.begin(9600)");

  Serial.print(F("FREE RAM: "));
  Serial.println(freeRam());

  httpServerSetup();
  ds18b20Setup();
  yfb5InterruptSetup();
  gy521Setup();
  servoSetup();

  wdt_enable(WDTO_8S);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            loop
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loop() {
  wdt_reset();
  playSound();
  realTimeService();
  resetChecker();


  if (millis() > lastSpeakTime) {
    lastSpeakTime += TONE_STATUS_TIMEOUT;
    uint8_t address[8] = { 0x28, 0xFF, 0xBB, 0x7E, 0x62, 0x18, 0x01, 0xE4 };

    int temp = ds18Sensors.getTempC(address);

    if (temp > 94) {
      addSound(toneBWCritical);
    } else if (temp > 93) {
      addSound(toneBWWarning);
    } else if (temp > 88) {
      addSound(toneBWHigh);
    } else {
      addSound(toneBWNormal);
    }

    int max6675Now = thermocouple.readCelsius();
    if (max6675Now > 350) {
      addSound(toneBWCritical);
    } else if (max6675Now > 300) {
      addSound(toneBWWarning);
    } else if (max6675Now > 250) {
      addSound(toneBWHigh);
    } else {
      addSound(toneBWNormal);
    }
  }


}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            info
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\

28.01.2021 v11 Reset: disabled 3min reset; 30days still works
16.01.2021 v10 Reset added (30days uptime, and 3minutes no requests)
01.02.2020 v9 add Servo995
02.01.2020 v8.0 Переход на блочно-модульное программирование 
25.12.2019 v7.0 добавлено измерение угла заслонки на базе GY-521
13.11.2019 v6.0 переход на статические IP
10.03.2019 v5.0 время работы после включения
06.03.2019 v4.4 add HX711 for PT100, dell PT1000 
02.03.2019 v4.3 add PT1000-smoke
14.02.2019 v4.2 заменен датчик PT100, откалиброван
06.02.2019 v4.1 изменение вывода №№ DS18 и префикс заменен на "bw-"
06.02.2019 v4.0 структура JSON без <ArduinoJson.h>
06.02.2019 v3.1 добавлен префикс к переменным "boiler-wood-"
04.02.2019 v3.0 добавлена функция freeRam()
09.01.2019 v2.7 static int flowSensorPulsesPerSecond на unsigned long
30.12.2018 v2.6 в json замена на ds18In, ds18Out, ds18FromTA
24.12.2018 v2.5 json structure updated
24.12.2018 v2.4 повышение розрядности измерения PT100 и датчика давления
24.12.2018 v2.3 flow sensor calc switch to pulses per second
23.12.2018 v2.2 PT100 nominalR = 220 om и 1 ком
20.12.2018 v2.1 dell PT1000
06.12.2018 v2.0 add DS18B20
05.12.2018 v1

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            end
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
