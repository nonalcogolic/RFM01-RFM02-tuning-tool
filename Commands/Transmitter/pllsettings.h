#ifndef PLLSETTINGS_H
#define PLLSETTINGS_H

#include "../ACommands.h"

namespace NTransmitter
{

class PLLSettings : public ACommands
{
public:
   PLLSettings();
   enum class eMaxBitrate
   {
      br_19_2 = 0x4,
      br_38_4 = 0xC,
      br_68_9 = 0x0,
      br_115_2 = 0x8
   };

   void setPllValue(const eMaxBitrate br);
   void setPllValue(const int32_t br);
};

}

#endif // PLLSETTINGS_H
