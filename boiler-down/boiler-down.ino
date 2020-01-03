/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
                                                   boiler-down.ino
                            Copyright © 2018-2020, Zigfred & Nik.S
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\                            
31.12.2018 v1
03.01.2019 v1.2 откалиброваны коэфициенты трансформаторов тока
10.01.2019 v1.3 изменен расчет в YF-B5
11.01.2019 v1.4 переименование boiler6kw в boilerDown
23.01.2019 v1.5 добавлены ds18 ТА и в №№ ds18 только 2 знака 
28.01.2019 v1.6 переименование boilerDown в boiler-down
03.02.2019 v1.7 преобразование в формат  F("")
04.02.2019 v1.8 переменные с префиксом boiler-down-
04.02.2019 v1.9 в вывод добавлено ("data: {")
04.02.2019 v1.10 добавлена функция freeRam()
06.02.2019 v1.11 изменение вывода №№ DS18 и префикс заменен на "bd-"
10.02.2019 v1.12 удален intrevalLogService
10.02.2019 v1.13 добавлено измерение уровня воды (дальномер HC-SR04)
13.11.2019 v1.14 переход на статические IP
02.01.2020 v2 Переход на модульное программирование 
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
  Arduino Pro Mini:
Скетч использует 19762 байт (64%) памяти устройства. 
Глобальные переменные используют 769 байт (37%) динамической памяти.
/*******************************************************************\
  Сервер boiler-down выдает данные:
    аналоговые:
датчики трансформаторы тока
    цифровые:
датчик скорости потока воды YF-B5 (количество импульсов за 15 сек)
датчики температуры DS18B20
дальномер HC-SR04 (измерение уровня воды)
/*******************************************************************/

#include <Ethernet2.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <EmonLib.h>
#include <RBD_Timer.h>
#include <hcsr04.h>
//-------------------------------------------------------------------
#define DEVICE_ID "boiler-down";
//String DEVICE_ID "boiler6kw";
#define VERSION 2
//-------------------------------------------------------------------
#define RESET_UPTIME_TIME 43200000  //  = 30 * 24 * 60 * 60 * 1000 
// reset after 30 days uptime
//-------------------------------------------------------------------
byte mac[] = {0xCA, 0x74, 0xBA, 0xCE, 0xBE, 0x01};
IPAddress ip(192, 168, 1, 102);
EthernetServer httpServer(40102); // Ethernet server
//-------------------------------------------------------------------
EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;
//-------------------------------------------------------------------
#define PIN_ONE_WIRE_BUS 9
uint8_t ds18Precision = 11;
#define DS18_CONVERSION_TIME 750 / (1 << (12 - ds18Precision))
unsigned short ds18DeviceCount;
bool isDS18ParasitePowerModeOn;
OneWire ds18wireBus(PIN_ONE_WIRE_BUS);
DallasTemperature ds18Sensors(&ds18wireBus);
//-------------------------------------------------------------------
#define PIN_FLOW_SENSOR 2
#define PIN_INTERRUPT_FLOW_SENSOR 0
#define FLOW_SENSOR_CALIBRATION_FACTOR 5
//byte flowSensorInterrupt = 0; // 0 = digital pin 2
volatile long flowSensorPulseCount = 0;
//-------------------------------------------------------------------
unsigned long currentTime;
unsigned long flowSensorLastTime;

RBD::Timer ds18ConversionTimer;
//-------------------------------------------------------------------
#define TRIG_PIN 1
#define ECHO_PIN 3
HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 30, 4000); // пределы: от и до
int taLevelWater;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void setup() {
  Serial.begin(9600);
  Serial.println("Serial.begin(9600)"); 

  setuphttpServer();
  
  setupInterrupt();
  
  setupDs18Sensors();
  
  Serial.print(F("FREE RAM: "));
  Serial.println(freeRam());

  pinMode( A1, INPUT );
  pinMode( A2, INPUT );
  pinMode( A3, INPUT );
  emon1.current(1, 9.3);
  emon2.current(2, 9.27);
  emon3.current(3, 9.29);
  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            loop
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loop() {
  currentTime = millis();
  
  realTimeService();
  
  resetWhen30Days();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            end
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
