/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            settings collector
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	#include "collector_floor_init.h"

//	Блок httpServer	-----------------------------------------------------------
byte mac[] = {0xCA, 0x74, 0xC0, 0xFF, 0xCF, 0x01};
IPAddress ip(192, 168, 1, 113);
EthernetServer httpServer(40113);

//	Блок DS18B20  -------------------------------------------------------------
#define PIN9_ONE_WIRE_BUS 9 
#define DS18_CONVERSION_TIME 750 // (1 << (12 - ds18Precision))
#define DS18_PRECISION = 11

OneWire ds18wireBus(PIN9_ONE_WIRE_BUS);
DallasTemperature ds18Sensors(&ds18wireBus);
uint8_t ds18DeviceCount;

RBD::Timer ds18ConversionTimer;

//  Блок flow YF-B5  ----------------------------------------------------------
volatile long flowSensorPulseCountA0 = 0;
volatile long flowSensorPulseCountA1 = 0;
volatile long flowSensorPulseCountA2 = 0;
volatile long flowSensorPulseCountA3 = 0;
volatile long flowSensorPulseCountA4 = 0;
volatile long flowSensorPulseCountA5 = 0;
volatile long flowSensorPulseCount2 = 0;
//volatile long flowSensorPulseCount3 = 0;	//	резерв для 8-й ветки

// time
uint32_t flowSensorLastTimeA0;
uint32_t flowSensorLastTimeA1;
uint32_t flowSensorLastTimeA2;
uint32_t flowSensorLastTimeA3;
uint32_t flowSensorLastTimeA4;
uint32_t flowSensorLastTimeA5;
uint32_t flowSensorLastTime2;
//uint32_t flowSensorLastTime3;	//	резерв для 8-й ветки

//  Блок Servo996R  -----------------------------------------------------------
Servo servo996r;

//	Блок TIME  ----------------------------------------------------------------
#define RESET_UPTIME_TIME 43200000  //  = 30 * 24 * 60 * 60 * 1000 
// reset after 30 days uptime

// reset when 3min no requests from collector
#define RESET_ON_SILENCE_TIMEOUT 20000  //  = 3 * 60 * 1000
unsigned long lastRequestTime = 0;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/