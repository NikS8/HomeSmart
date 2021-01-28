/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            settings boiler_wood
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	#include "boiler_wood_init.h"

//	Блок httpServer	-----------------------------------------------------------
byte mac[] = {0xCA, 0x74, 0xC0, 0xFF, 0xBD, 0x01};
IPAddress ip(192, 168, 1, 111);
EthernetServer httpServer(40111);

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
volatile long yfb5PulseCount = 0;
// time
unsigned long yfb5LastTime;

//  Блок pressure  ------------------------------------------------------------
#define PIN_PRESSURE_SENSOR A0

//  Блок GY-521 MPU6050  ------------------------------------------------------
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t accelY;

// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.

#define OUTPUT_READABLE_ACCELGYRO

//  Блок Servo996R  -----------------------------------------------------------
Servo servomotor;

//	Блок TIME  ----------------------------------------------------------------
#define RESET_UPTIME_TIME 43200000  //  = 30 * 24 * 60 * 60 * 1000 
// reset after 30 days uptime

//  Блок max6675  -------------------------------------------------------------

/*
MISO: SOMI, SDO (на устройстве), DO, DON, SO, MRSR;
MOSI: SIMO, SDI (на устройстве), DI, DIN, SI, MTST;
SCLK: SCK, CLK, SPC (SPI serial port clock);
SS: nCS, CS, CSB, CSN, NSS, nSS, STE, SYNC.

sck 6 SCLK
cs 7 SS
so 8 MISO
*/

#define PIN6_MAX6675_CLK 6 // SCLK
#define PIN6_MAX6675_CS 7  // SS
#define PIN6_MAX6675_DO 8  // MISO

MAX6675 thermocouple(PIN6_MAX6675_CLK, PIN6_MAX6675_CS, PIN6_MAX6675_DO);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
