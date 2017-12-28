#include "configurationsetting.h"

ConfigurationSetting::ConfigurationSetting()
   : ACommands(0x80,0x00)
{}


void ConfigurationSetting::setFrequency(const eFrequency freq)
{
   setValue(11, 2, static_cast<int>(freq));
}

void ConfigurationSetting::setClkFrequency(const eClockFrequency freq)
{
   setValue(8, 3, static_cast<int>(freq));
}

void ConfigurationSetting::setCrystalLoadCapasitance(const int8_t pf)
{
   uint8_t value = (pf - 85) / 5;
   if (value > 0xE) value = 0xE;
   setValue(4, 4, value);
}

void ConfigurationSetting::setOutputBandwidth(const eBandwidth_khz bandwidth)
{
   setValue(0, 3, static_cast<int>(bandwidth));
}

void ConfigurationSetting::setBandwidthSign(const bool positive)
{
   setValue(3, 1, positive ? 1 : 0);
}
