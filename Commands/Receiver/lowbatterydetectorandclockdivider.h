#ifndef LOWBATTERYDETECTORANDCLOCKDIVIDER_H
#define LOWBATTERYDETECTORANDCLOCKDIVIDER_H

#include "../ACommands.h"

namespace Receiver
{

class LowBatteryDetectorAndClockDivider : public ACommands
{
public:
   LowBatteryDetectorAndClockDivider();

   enum class eCLKfrequncy
   {
      clk_1 = 0,
      clk_1_25,
      clk_1_33,
      clk_2,
      clk_2_5,
      clk_3_33,
      clk_5,
      clk_10
   };


   void setOutputCLKFrequency(const eCLKfrequncy clk);

   void setTresholdValue(const uint8_t voltage); //scale 1:10
   void setTresholdValue(const double voltage);
};


}

#endif // LOWBATTERYDETECTORANDCLOCKDIVIDER_H
