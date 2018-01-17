#ifndef FREQUENCYSETTING_RECEIVER_H
#define FREQUENCYSETTING_RECEIVER_H

#include "../ACommands.h"

namespace Receiver
{

class FrequencySetting : public ACommands
{
public:
   FrequencySetting();

   //430.240000 ~ 439.757500  Mhz. Value in Hz should be used.
   void setFrequency(const uint32_t frequency);
};


}

#endif // FREQUENCYSETTING_RECEIVER_H
