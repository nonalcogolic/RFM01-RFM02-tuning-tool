#ifndef IPINOUT_H
#define IPINOUT_H

#include "helper.h"

enum class ePin
{
   nSel = 23,
   SDI = 10,
   SDO = 9,
   SCK = 11,
   nIRQ = 24,

   tr_SDI = 2,
   tr_SCK = 3 ,
   tr_nSEL = 4,
   tr_NIRQ = 17,
   tr_FSK //not configurated yet
};


class IPinOut
{
public:
   virtual ~IPinOut() = default;
   virtual void setPinState(const bool state, const ePin pin) = 0;
   virtual void setPinStateForce(const bool state, const ePin pin) = 0;
   virtual bool getPinState(const ePin pin) = 0;
   virtual void setPinDirrection(const bool isPinOut, const ePin pin) = 0;

   virtual void subscribeOn(const ePin pin, const eEventType type) = 0;
   virtual void unsubscribeFrom(const ePin pin, const eEventType type) = 0;
   virtual bool checkEvent(const ePin pin) = 0;
   virtual void resetEvent(const ePin pin) = 0;
};


#endif // IPINOUT_H
