/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            settings boiler_wood
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	#include "boiler_wood_init.h"

//	Блок RS485	-----------------------------------------------------------
int statePin;      //  статус Pin
EasyTransfer ETin, ETout;  //create two objects
#define DIR 13            // переключатель прием\передача на Pin13

int ID = 11;              // номер этой ардуины 

int bw_dsBoilerN;
int bw_dsBoilerInN;
int bw_dsBoilerOutN;

struct RECEIVE_DATA_STRUCTURE {         // структура, которую будем принимать
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int ID;
  int action;
  int targetPin;
  int levelPin;
};
int action = 0;    //  0/1 ("get"/"set") - запрос выдачи данных / команда на исполнение
int levelPin = 0;       //  0/1 - установка уровня на Pin (LOW/HIGH)
int targetPin = 9;          //  Pin управления

struct SEND_DATA_STRUCTURE {                  // структура, которую будем передавать
  int ID;
  int bw_pressure;    // температура от датчика давления в трубе от бака
  int bw_tPT100_smoke;       // температура от датчика DS18B20 на стенке бака внизу
  int bw_flow;    // температура от датчика DS18B20 на стенке бака посередине
  int bw_gy_shutter;      // температура от датчика DS18B20 на стенке бака вверху
  int bw_servo_shutter;    // температура от датчика DS18B20 внутри бака
  int bw_dsBoilerN;        // температура от датчика DS18B20 на выходном патрубке котла
  int bw_dsBoiler;        // температура от датчика DS18B20 на выходном патрубке котла
  int bw_dsBoilerInN;    // температура от датчика DS18B20 на трубе в бак
  int bw_dsBoilerIn;    // температура от датчика DS18B20 на трубе в бак
  int bw_dsBoilerOutN;   // температура от датчика DS18B20 на трубе из бака
  int bw_dsBoilerOut;   // температура от датчика DS18B20 на трубе из бака
  int statePin;      //  статус Pin
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE rxdata;
SEND_DATA_STRUCTURE txdata;
//////////////////////////

int maxValue;

//	Блок DS18B20  -------------------------------------------------------------
#define PIN9_ONE_WIRE_BUS 9 
#define DS18_CONVERSION_TIME 750 // (1 << (12 - ds18Precision))
#define DS18_PRECISION = 11

OneWire ds18wireBus(PIN9_ONE_WIRE_BUS);
DallasTemperature ds18Sensors(&ds18wireBus);
uint8_t ds18DeviceCount;

RBD::Timer ds18ConversionTimer;

//  Блок flow YF-B5  ----------------------------------------------------------
//#define PIN_YFB5 2
#define PIN_YFB5 6
#define PIN_INTERRUPT_YFB5 0
#define YFB5_CALIBRATION_FACTOR 5
//byte yfb5Interrupt = 0; // 0 = digital pin 2
volatile long yfb5PulseCount = 0;
unsigned long yfb5LastTime;
unsigned long currentTime;


//  Блок pressure  ------------------------------------------------------------
#define PIN_PRESSURE_SENSOR A0

//  Блок PPT100 HX711  --------------------------------------------------------
//https://github.com/bogde/HX711

#define UMIN  900000
#define UMAX 8000000
#define RMIN    80.0
#define RMAX   400.0

HX711 get_U;
//  https://forum.arduino.cc/index.php?topic=432678.0

const long  Uu = 1987905;//..1987230;// Rohmesswert unteres Ende
const long  Uo = 2800333;//4112725 318*;//4153141;// Rohmesswert oberes Ende
const float Ru = 106.7; // 17* // Widerstandswert unteres Ende
const float Ro = 177.1;//200**//220.5;// 318* // Widerstandswert oberes Ende

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
