/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            settings boiler_down
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	#include "boiler_down_init.h"

//	Блок httpServer	-----------------------------------------------------------
byte mac[] = {0xCA,0x74,0xBA,0xCE,0xBE,0x01};
IPAddress ip(192,168,1,102);
EthernetServer httpServer(40102);

//	Блок DS18B20  -------------------------------------------------------------
#define PIN_WIRE_BUS_BD 40
#define PIN_WIRE_BUS_BT 41
#define PIN_WIRE_BUS_TA 42
#define PIN_WIRE_BUS_HP 43
#define DS18_CONVERSION_TIME 750 // (1 << (12 - ds18Precision))
#define DS18_PRECISION = 11

OneWire ds18wireBD(PIN_WIRE_BUS_BD);
DallasTemperature ds18SensorsBD(&ds18wireBD);
uint8_t ds18DeviceCountBD;

OneWire ds18wireBT(PIN_WIRE_BUS_BT);
DallasTemperature ds18SensorsBT(&ds18wireBT);
uint8_t ds18DeviceCountBT;

OneWire ds18wireTA(PIN_WIRE_BUS_TA);
DallasTemperature ds18SensorsTA(&ds18wireTA);
uint8_t ds18DeviceCountTA;

OneWire ds18wireHP(PIN_WIRE_BUS_HP);
DallasTemperature ds18SensorsHP(&ds18wireHP);
uint8_t ds18DeviceCountHP;

RBD::Timer ds18ConversionTimer;

//  Блок flow YF-B5  ----------------------------------------------------------
#define PIN_YFB5_IN_BOILER 2
#define PIN_YFB5_IN_TA 3
#define PIN_INTERRUPT_YFB5 0
#define YFB5_CALIBRATION_FACTOR 5
//byte yfb5Interrupt = 0; // 0 = digital pin 2
volatile long yfb5PulseCountTA = 0;
volatile long yfb5PulseCountBoiler = 0;
unsigned long yfb5LastTimeTA;
unsigned long yfb5LastTimeBoiler;

//  Блок pressure  ------------------------------------------------------------
#define PIN_SENSOR_PRESSURE A0

//  Блок Energy Monitor  ------------------------------------------------------
#define PIN_EMON1 A1
#define PIN_EMON2 A2
#define PIN_EMON3 A3
#define PIN_EMON4 A4
#define PIN_EMON5 A5
#define PIN_EMON6 A6
#define PIN_EMON7 A0

float current_koef1 = 9.3;
float current_koef2 = 1;
float current_koef3 = 1;
float current_koef4 = 1;
float current_koef5 = 1;
float current_koef6 = 1;
float current_koef7 = 1;    // Калибровка при float current_koef7 = 1;

EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;
EnergyMonitor emon4;
EnergyMonitor emon5;
EnergyMonitor emon6;
EnergyMonitor emon7;

//  Блок HC-SR04  -------------------------------------------------------------
#define PIN_TRIG 22
#define PIN_ECHO 23
HCSR04 hcsr04(PIN_TRIG, PIN_ECHO, 30, 4000); // пределы: от и до
int taLevelWater;

//  Блок flow YF-B5  ----------------------------------------------------------

#define PIN_INTERRUPT_YFB5_BOILER 2
#define PIN_INTERRUPT_YFB5_TA 3

volatile long sensorPulseCountBoiler = 0;
volatile long sensorPulseCountTA = 0;

uint32_t sensorPulseLastTimeBoiler;
uint32_t sensorPulseLastTimeTA;

//  Блок Servo996R  -----------------------------------------------------------
#define PIN_SERVO_IN 4
Servo servo996in;
#define PIN_SERVO_OUT 5
Servo servo996out;

//	Блок TIME  ----------------------------------------------------------------
#define RESET_UPTIME_TIME 43200000  //  = 30 * 24 * 60 * 60 * 1000 
// reset after 30 days uptime

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/