#include "datarate.h"

#include <math.h>

namespace Receiver
{

DataRate::DataRate()
   : ACommands(0xC8,0x00)
{

}

void DataRate::setDataRate(const int32_t dataRate)
{
   if (337 <= dataRate && dataRate <= 115200)
   {
      int8_t value =  round(10000000 / 29 / 1 / dataRate - 1);
      if (value <= 127)
      {
         setValue(0, 7, value);
      }
      else
      {
         value =  round(10000000 / 29 / 8 / dataRate - 1);
         if (value <= 127)
         {
            setValue(0, 7, value);
            setValue(7, true);
         }
      }
   }
}

}
