#ifndef CONFIGURATIONSETTING_RECEIVER_H
#define CONFIGURATIONSETTING_RECEIVER_H

#include "../ACommands.h"

namespace Receiver
{

class ConfigurationSetting : public ACommands
{
public:
   ConfigurationSetting();

   enum class eFrequencyBand
   {
      fr_315 = 0,
      fr_433,
      fr_868,
      fr_915
   };
   enum class eBaseband
   {
      base_400 = 1,
      base_340 = 2,
      base_270 = 3,
      base_200 = 4,
      base_134 = 5,
      base_67 = 6
   };

   void setFrequencyBand(const eFrequencyBand band);
   void enableLowBatteryDetector(const bool enabled);
   void enableWakeUpTimerDetector(const bool enabled);
   void enableOscilator(const bool enabled);
   void setCrystalLoadCapasitance(const int8_t pf); //8.5-16  Scale: 1/10, to set 8.5 value equal 85 should be used
   void setBaseBandWidth(const eBaseband base);
   void disableCLKOutput(const bool disable);
};


}

#endif // CONFIGURATIONSETTING_RECEIVER_H
