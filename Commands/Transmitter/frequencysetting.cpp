#include "frequencysetting.h"

namespace NTransmitter
{

FrequencySetting::FrequencySetting()
   : ACommands(0xA0, 0x00)
{

}

void FrequencySetting::setFrequency(const uint32_t frequency)
{
   int16_t value =(frequency-430000000)/2500;

   if (96 <= value && value <= 3903)
   {
      setValue(0,12, value);
   }
}

}
