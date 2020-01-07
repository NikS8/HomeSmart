/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            init YF-B5
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//#include "yfb5_init_cf.h"
/*
#define PIN_YFB5 2
#define PIN_INTERRUPT_YFB5 0
#define YFB5_CALIBRATION_FACTOR 5
//byte yfb5Interrupt = 0; // 0 = digital pin 2
*/
//volatile long yfb5PulseCount = 0;
//unsigned long yfb5LastTime;


//00000000000000
volatile long flowSensorPulseCountA0 = 0;
volatile long flowSensorPulseCountA1 = 0;
volatile long flowSensorPulseCountA2 = 0;
volatile long flowSensorPulseCountA3 = 0;
volatile long flowSensorPulseCountA4 = 0;
volatile long flowSensorPulseCountA5 = 0;
volatile long flowSensorPulseCount2 = 0;
//volatile long flowSensorPulseCount3 = 0;
// time
uint32_t flowSensorLastTimeA0;
uint32_t flowSensorLastTimeA1;
uint32_t flowSensorLastTimeA2;
uint32_t flowSensorLastTimeA3;
uint32_t flowSensorLastTimeA4;
uint32_t flowSensorLastTimeA5;
uint32_t flowSensorLastTime2;
//uint32_t flowSensorLastTime3;
  
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
