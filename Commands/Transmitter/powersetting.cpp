#include "powersetting.h"

namespace NTransmitter
{

PowerSetting::PowerSetting()
   : ACommands(0xB0)
{

}

void PowerSetting::setOutputPower(const uint8_t power)
{
   const auto value = power & 0x07;
   setValue(0,3, value);
}

}
