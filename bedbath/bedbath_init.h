/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            settings bedbath
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	#include "bedbath_init.h"

//	Блок httpServer	-----------------------------------------------------------
byte mac[] = {0xCA, 0x74, 0xBE, 0xBA, 0xFF, 0x01};
IPAddress ip(192, 168, 1, 161);
EthernetServer httpServer(40161);

//  Блок Energy Monitor  ------------------------------------------------------
EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;

//  Блок DHT  -----------------------------------------------------------------
#define DHT1TYPE DHT22 
#define DHT1PIND 9      // PIN подключения датчика DTH22
DHT dht1(DHT1PIND, DHT1TYPE);
float sensorDhtTemp;    // температура от датчика DHT22 
int sensorDhtHum;       // влажность от датчика DHT22

//	Блок TIME  ----------------------------------------------------------------
#define RESET_UPTIME_TIME 43200000  //  = 30 * 24 * 60 * 60 * 1000 
// reset after 30 days uptime

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/