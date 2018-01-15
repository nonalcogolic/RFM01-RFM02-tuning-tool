#ifndef LOWDUTYCYCLE_H
#define LOWDUTYCYCLE_H

#include "../ACommands.h"

namespace Receiver
{

class LowDutyCycle : public ACommands
{
public:
   LowDutyCycle();

   void setDutyCycle(const int8_t cycle);
   void enableLowDutyCycle(const bool enable);

};


}

#endif // LOWDUTYCYCLE_H
