#ifndef DATAFILTER_RECEIVER_H
#define DATAFILTER_RECEIVER_H

#include "../ACommands.h"

namespace Receiver
{

enum class eDataFilterType
{
   OOK = 0,
   DigitalFilter = 1,
   AnalogRC = 3
};

class DataFilter : public ACommands
{
public:
   DataFilter();

   void enableAutoClockRecovery(const bool enabled);
   void onClockRecovery(const bool active);
   void setDataFilterType(const eDataFilterType type);
   void setDQDparams(const int8_t value);
};


}

#endif // DATAFILTER_RECEIVER_H
