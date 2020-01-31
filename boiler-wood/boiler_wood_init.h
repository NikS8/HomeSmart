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
unsigned long currentTime;
unsigned long yfb5LastTime;

//  Блок pressure  ------------------------------------------------------------
#define PIN_PRESSURE_SENSOR A0

//  Блок PPT100 HX711  --------------------------------------------------------
//https://github.com/bogde/HX711

#define UMIN  900000
#define UMAX 8000000
#define RMIN    80.0
#define RMAX   500.0

HX711 get_U;
//  https://forum.arduino.cc/index.php?topic=432678.0

const long  Uu = 1529333;//1533333;//1539999;//1538853;   // Rohmesswert unteres Ende
const long  Uo = 2224222;//1977777;//1948677 +18    // Rohmesswert oberes Ende
const float Ru = 108.7; // 22 // Widerstandswert unteres Ende
const float Ro = 184.5;// 220 // Widerstandswert oberes Ende

long Umess;
float Rx, tempPT100;

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
int16_t accelX;

// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.

#define OUTPUT_READABLE_ACCELGYRO

//	Блок TIME  ----------------------------------------------------------------
#define RESET_UPTIME_TIME 43200000  //  = 30 * 24 * 60 * 60 * 1000 
// reset after 30 days uptime

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
