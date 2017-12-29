#ifndef POWERMANAGEMENT_H
#define POWERMANAGEMENT_H

#include "../ACommands.h"

namespace NTransmitter
{

class PowerManagement : ACommands
{
public:
   PowerManagement();

   void disableClockOut(const bool disable);
   void activateOscillator(const bool active);
   void activateSynthesizer(const bool active);
   void activateAmplifter(const bool active);
   void activateLowBatteryDetector(const bool active);
   void activateWakeUpTimer(const bool active);

   //ex,ea,es should be 0.
   void automaticOscilatorAndSynthesizer(const bool active);
   void automaticPowerAmplifter(const bool active);
};

}

#endif // POWERMANAGEMENT_H
