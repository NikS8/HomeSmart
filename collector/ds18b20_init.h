/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            init DS18B20
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//#include "ds18b20_init.h"

#define PIN_ONE_WIRE_BUS 9
#define DS18_CONVERSION_TIME 750 / (1 << (12 - ds18Precision))

OneWire ds18wireBus(PIN_ONE_WIRE_BUS);
DallasTemperature ds18Sensors(&ds18wireBus);

uint8_t ds18Precision = 11;
unsigned short ds18DeviceCount;
bool isDS18ParasitePowerModeOn;

RBD::Timer ds18ConversionTimer;
  
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
