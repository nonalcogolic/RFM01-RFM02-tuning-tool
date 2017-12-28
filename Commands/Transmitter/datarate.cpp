#include "datarate.h"

#include <math.h>

DataRate::DataRate()
   : ACommands(0xC8, 0x00)
{

}

void DataRate::setDataRate(const int32_t dataRate)
{
   int8_t value =  round(10000000 / 29 / dataRate - 1);
   setValue(0, 8, value);
}
