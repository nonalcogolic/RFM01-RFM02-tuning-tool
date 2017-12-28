#include "lowbatteryandtxbitsync.h"

LowBatteryAndTXbitSync::LowBatteryAndTXbitSync()
   : ACommands(0xC2,0x00)
{}

void LowBatteryAndTXbitSync::disableWakeTimerColibration(const bool disable)
{
   setValue(7, disable);
}

void LowBatteryAndTXbitSync::enableTXSyncr(const bool enable)
{
   setValue(5, enable);
}

void LowBatteryAndTXbitSync::setTresholdValue(const uint8_t voltage)
{
   if (voltage < 5.3)
   {
      const uint8_t value = (voltage - 2.2) * 10;
      setValue(0, 5, value);
   }
}
