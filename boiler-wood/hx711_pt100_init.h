/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            init HX711
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//#include "hx711_pt100_init.h"
HX711 get_U;
#define UMIN  100000
#define UMAX 9000000
#define RMIN    10.0
#define RMAX   700.0

const long  Uu = 1477777; //1499999 17 при25; // 1333333 62 при23;//1842181 это -100 при21;//1557878 это -1 при21;//1563838;//1568248;//1842181;    // Rohmesswert unteres Ende  
const long  Uo = 3444444; //3577777 130 при 145; //  3588888 144 при134;    //3599999 167 при157;    //4792792 это 145 при200;//4777449;    // Rohmesswert oberes Ende 
const float Ru = 104;   //110.5;  // Widerstandswert unteres Ende
const float Ro = 345;   //333.0;  // Widerstandswert oberes Ende

long Umess;
float Rx, tempPT100;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
