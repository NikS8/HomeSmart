/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            settings boiler_reserve
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	#include "boiler_reserve_init.h"

//	Блок httpServer	-----------------------------------------------------------
byte mac[] = {0xCA, 0x74, 0xC0, 0xFF, 0xBE, 0x01};
IPAddress ip(192, 168, 1, 112);
EthernetServer httpServer(40112); 

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
//byte yfb5Interrupt = 0; // 0 = digital pin 2
volatile long yfb5PulseCount = 0;
unsigned long yfb5LastTime;
unsigned long currentTime;

//  Блок pressure  ------------------------------------------------------------
#define PIN_PRESSURE_SENSOR A0

//  Блок Energy Monitor  ------------------------------------------------------
EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;

//	Блок TIME  ----------------------------------------------------------------
#define RESET_UPTIME_TIME 43200000  //  = 30 * 24 * 60 * 60 * 1000 
// reset after 30 days uptime

// reset when 3min no requests from collector
#define RESET_ON_SILENCE_TIMEOUT 20000  //  = 3 * 60 * 1000 
unsigned long lastRequestTime = 0;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
