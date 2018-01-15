#include "lowdutycycle.h"


namespace Receiver
{

LowDutyCycle::LowDutyCycle()
   : ACommands(0xCC,0x00)
{}

void LowDutyCycle::setDutyCycle(const int8_t cycle)
{
   if (!(cycle & 0x80))
   {
      setValue(1, 7, cycle);
   }
}

void LowDutyCycle::enableLowDutyCycle(const bool enable)
{
   setValue(0, enable);
}

}
