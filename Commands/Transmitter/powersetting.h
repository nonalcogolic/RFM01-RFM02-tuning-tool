#ifndef POWERSETTING_H
#define POWERSETTING_H


#include "../ACommands.h"

namespace NTransmitter
{

class PowerSetting : public ACommands
{
public:
   PowerSetting();

   void setOutputPower(const uint8_t power);
};

}

#endif // POWERSETTING_H
