#ifndef LOWBATTERYANDTXBITSYNC_H
#define LOWBATTERYANDTXBITSYNC_H

#include "../ACommands.h"

namespace NTransmitter
{


class LowBatteryAndTXbitSync : public ACommands
{
public:
   LowBatteryAndTXbitSync();

   void disableWakeTimerColibration(const bool disable);
   void enableTXSyncr(const bool enable);
   void setTresholdValue(const uint8_t voltage); //scale 1:10
   void setTresholdValue(const double voltage);
};

}

#endif // LOWBATTERYANDTXBITSYNC_H
