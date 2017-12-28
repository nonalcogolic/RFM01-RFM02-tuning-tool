#include "powermanagement.h"

PowerManagement::PowerManagement()
   : ACommands(0xC0, 0x00)
{

}

void PowerManagement::disableClockOut(const bool disable)
{
   setValue(0, disable);
}

void PowerManagement::activateOscillator(const bool active)
{
   setValue(5, active);
}

void PowerManagement::activateSynthesizer(const bool active)
{
   setValue(4, active);
}

void PowerManagement::activateAmplifter(const bool active)
{
   setValue(3, active);
}

void PowerManagement::activateLowBatteryDetector(const bool active)
{
   setValue(2, active);
}

void PowerManagement::activateWakeUpTimer(const bool active)
{
   setValue(1, active);
}

void PowerManagement::automaticOscilatorAndSynthesizer(const bool active)
{
   setValue(7, active);
}

void PowerManagement::automaticPowerAmplifter(const bool active)
{
   setValue(6, active);
}
