#include "lowbatterydetectorandclockdivider.h"


namespace Receiver
{

LowBatteryDetectorAndClockDivider::LowBatteryDetectorAndClockDivider()
   : ACommands(0xC2,0x00)
{}

void LowBatteryDetectorAndClockDivider::setOutputCLKFrequency(const eCLKfrequncy clk)
{
   setValue(5, 3, clk);
}

void LowBatteryDetectorAndClockDivider::setTresholdValue(const uint8_t voltage)
{
   if (voltage <= 53)
   {
      const uint8_t value = voltage - 22;
      setValue(0, 5, value);
   }
}

void LowBatteryDetectorAndClockDivider::setTresholdValue(const double voltage)
{
   if (voltage <= 5.3)
   {
      const uint8_t value = (voltage - 2.2) * 10;
      setValue(0, 5, value);
   }
}

}
