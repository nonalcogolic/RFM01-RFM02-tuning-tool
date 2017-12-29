#ifndef SLEEP_H
#define SLEEP_H

#include "../ACommands.h"

namespace NTransmitter
{

class Sleep : public ACommands
{
public:
   Sleep();

   void setSleepAfter(const uint8_t delayTicks);
};

}

#endif // SLEEP_H
