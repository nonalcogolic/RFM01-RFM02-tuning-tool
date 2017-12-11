#ifndef IPINOUT_H
#define IPINOUT_H

#include <bcm2835.h>

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
   tr_NIRQ = 17
};


class IPinOut
{
public:
   virtual ~IPinOut() = default;
   virtual void setPinState(const bool state, const ePin pin) = 0;
   virtual bool getPinState(const ePin pin) = 0;
   virtual void setPinDirrection(const bool isPinOut, const ePin pin) = 0;
};

class PinOutDummy : public IPinOut
{
public:
   void setPinState(const bool state, const ePin pin) override {  (void) state; (void) pin; }
   bool getPinState(const ePin pin) override { (void) pin; return false; }
   virtual void setPinDirrection(const bool isPinOut, const ePin pin) {  (void) isPinOut;  (void) pin;}
};


#endif // IPINOUT_H
