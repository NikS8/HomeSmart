/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
                                                               boiler-wood.ino 
                                        Copyright © 2018-2020, Zigfred & Nik.S
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
  Сервер boiler-wood на Arduino Atmega328 Pro Mini:
Sketch uses 15,644 bytes (50.9%) of program storage space. Maximum is 30,720 bytes.
Global variables use 955 bytes (46.6%) of dynamic memory, 
leaving 1,093 bytes for local variables. Maximum is 2,048 bytes.
/*****************************************************************************\
 Сервер boiler-wood выдает данные:
  аналоговые: 
    датчик давления (A0)
    датчик температуры PT100 (A1, A2 HX711)
  цифровые: 
    датчик скорости потока воды YF-B5(D6) (количество импульсов за 15 сек)
    датчики температуры DS18B20 (D9)
    датчик угла GY-521 (I2C A4, A5)
    датчик угла от Servo995 (D5)
/*****************************************************************************/

//  Блок DEVICE  --------------------------------------------------------------
//  Arduino Atmega328 Pro Mini
#define DEVICE_ID "boiler-wood"
#define VERSION 11

//  Блок libraries  -----------------------------------------------------------
#include <SoftwareSerial.h>     //  RS485 pins D2, D3
#include <OneWire.h>            //  DS18B20  pin OneWire D9
#include <DallasTemperature.h>  //  DS18B20
#include <RBD_Timer.h>          //  DS18B20
#include <HX711.h>              //  PT100 (HX711 A1,A2)//github.com/bogde/HX711
#include <I2Cdev.h>             //  GY-521 (I2C A4,A5)
#include <MPU6050.h>            //  GY-521 
#include <Servo.h>              //  Servo995 pin 5
                                //  flow YF-B5 pin D6


//  Блок settings  ------------------------------------------------------------
#include "boiler_wood_init.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void setup() {
  
  Serial.begin(9600);
  Serial.println("Serial.begin(9600)");

  Serial.print(F("FREE RAM: "));
  Serial.println(freeRam());

  mySerial.begin(4800); // RS485

  
  ds18b20Setup();
  yfb5InterruptSetup();
  pt100hx711Setup();
  gy521Setup();
  servoSetup();


  pinMode( A0, INPUT );
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            loop
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loop() {
  
  ds18RequestTemperatures();

  parserDataString();

  outTxData();

  resetWhen30Days();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            info
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
07.03.2020 v11 RS485
21.02.2020 v10.0 Перевод некоторых функций в классы
01.02.2020 v9.0 add Servo995
02.01.2020 v8.0 Переход на блочно-модульное программирование 
25.12.2019 v7.0 добавлено измерение угла заслонки на базе GY-521
13.11.2019 v6.0 переход на статические IP
10.03.2019 v5.0 время работы после включения
06.03.2019 v4.4 add HX711 for PT100, dell PT1000 
02.03.2019 v4.3 add PT1000-smoke
14.02.2019 v4.2 заменен датчик PT100, откалиброван
06.02.2019 v4.1 изменение вывода №№ DS18 и префи кс заменен на "bw-"
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