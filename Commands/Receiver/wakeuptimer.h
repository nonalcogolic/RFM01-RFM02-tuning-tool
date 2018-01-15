#ifndef WAKEUPTIMER_H
#define WAKEUPTIMER_H

#include "../ACommands.h"

namespace Receiver
{

class WakeUpTimer : public ACommands
{
public:
   WakeUpTimer();

   void setPeriod(const uint8_t mantis, const uint8_t order);
};


}

#endif // WAKEUPTIMER_H
