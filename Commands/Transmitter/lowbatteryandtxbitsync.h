#ifndef LOWBATTERYANDTXBITSYNC_H
#define LOWBATTERYANDTXBITSYNC_H

#include "../ACommands.h"

class LowBatteryAndTXbitSync : public ACommands
{
public:
   LowBatteryAndTXbitSync();

   void disableWakeTimerColibration(const bool disable);
   void enableTXSyncr(const bool enable);
   void setTresholdValue(const uint8_t voltage);
};

#endif // LOWBATTERYANDTXBITSYNC_H
