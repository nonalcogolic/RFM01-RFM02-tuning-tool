#ifndef CBROADCOMPINOUT_H
#define CBROADCOMPINOUT_H

#include "ipinout.h"


class CBroadcomPinout : public IPinOut
{
public:
   CBroadcomPinout();
   ~CBroadcomPinout();

   void setPinState(const bool state, const ePin pin) override;
   void setPinStateForce(const bool state, const ePin pin) override;
   bool getPinState(const ePin pin) override;
   void setPinDirrection(const bool isPinOut, const ePin pin);

   void subscribeOn(const ePin pin, const eEventType type) override;
   void unsubscribeFrom(const ePin pin, const eEventType type) override;
   bool checkEvent(const ePin pin) override;
   void resetEvent(const ePin pin) override;
};

#endif // CBROADCOMPINOUT_H
