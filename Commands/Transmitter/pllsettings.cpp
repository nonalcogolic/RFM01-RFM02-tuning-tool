#include "pllsettings.h"

PLLSettings::PLLSettings()
   : ACommands(0xD2, 0x00)
{

}


void PLLSettings::setPllValue(const eMaxBitrate br)
{
   setValue(4,4,br);
}

void PLLSettings::setPllValue(const int32_t br)
{
   if (br < 19200)
   {
       setValue(4,4,eMaxBitrate::br_19_2);
   }
   else if (br < 38400)
   {
       setValue(4,4,eMaxBitrate::br_38_4);
   }
   else if (br < 68900)
   {
       setValue(4, 4, eMaxBitrate::br_68_9);
   }
   else
   {
       setValue(4,4,eMaxBitrate::br_115_2);
   }
}
