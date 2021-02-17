/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            settings boiler_down
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	#include "boiler_down_init.h"

//	Блок httpServer	-----------------------------------------------------------
byte mac[] = {0xCA, 0x74, 0xBA, 0xCE, 0xBE, 0x01};
IPAddress ip(192, 168, 1, 102);
EthernetServer httpServer(40102);

//	Блок DS18B20  -------------------------------------------------------------
#define PIN9_ONE_WIRE_BUS 9 
#define DS18_CONVERSION_TIME 750 // (1 << (12 - ds18Precision))
#define DS18_PRECISION = 11

OneWire ds18wireBus(PIN9_ONE_WIRE_BUS);
DallasTemperature ds18Sensors(&ds18wireBus);
uint8_t ds18DeviceCount;

RBD::Timer ds18ConversionTimer;

//  Блок flow YF-B5  ----------------------------------------------------------
#define PIN_YFB5 2
#define PIN_INTERRUPT_YFB5 0
#define YFB5_CALIBRATION_FACTOR 5
volatile long yfb5PulseCount = 0;
unsigned long yfb5LastTime;

//  Блок relay managed by http  ------------------------------------------------------------
// relay pin 8 is free
#define PIN_HEATER_RUN 7
#define PIN_HEATER_1 A4
#define PIN_HEATER_2 A5
#define PIN_HEATER_3 3
#define PIN_HEATER_4 4
#define PIN_HEATER_5 5
#define PIN_HEATER_6 6

byte heaterStatePins[] = {
  PIN_HEATER_RUN,
  PIN_HEATER_1,
  PIN_HEATER_2,
  PIN_HEATER_3,
  PIN_HEATER_4,
  PIN_HEATER_5,
  PIN_HEATER_6
};

//  Блок Energy Monitor  ------------------------------------------------------
EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;

//	Блок TIME  ----------------------------------------------------------------
#define RESET_UPTIME_TIME 3600000  //  //= 30 * 24 * 60 * 60 * 1000
// reset every 1 hour uptime

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
