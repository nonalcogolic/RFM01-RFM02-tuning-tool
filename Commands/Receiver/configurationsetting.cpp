#include "configurationsetting.h"


namespace Receiver
{

ConfigurationSetting::ConfigurationSetting()
   : ACommands(0x80,0x00)
{}

void ConfigurationSetting::setFrequencyBand(const eFrequencyBand band)
{
   setValue(11, 2, band);
}

void ConfigurationSetting::enableLowBatteryDetector(const bool enabled)
{
   setValue(10, enabled);
}

void ConfigurationSetting::enableWakeUpTimerDetector(const bool enabled)
{
   setValue(9, enabled);
}

void ConfigurationSetting::enableOscilator(const bool enabled)
{
   setValue(8, enabled);
}

void ConfigurationSetting::setCrystalLoadCapasitance(const int8_t pf)
{
   uint8_t value = (pf - 85) / 5;
   if (value > 0xF) value = 0xF;
   setValue(4, 4, value);
}

void ConfigurationSetting::setBaseBandWidth(const eBaseband base)
{
   setValue(1, 3, base);
}

void ConfigurationSetting::disableCLKOutput(const bool disable)
{
   setValue(0, disable);
}



}
