#ifndef IPINOUT_H
#define IPINOUT_H

#include "helper.h"

enum class ePin
{   

    /*test LED*/
    _test = 21,

   /* 22 - 23
      3V - 24
      10 - GND
      09 - 25
      11 - 8
           7  */

   VDI = 22,  SCK = 23,
   /*3V*/     SDO = 24,
   SDI = 10,  /*GND*/
   nSel = 9,  DATA = 25,  //Not used
   nIRQ = 11, CLK = 8, //NOT used yet
              FFIT = 7,

   /* 2 - 5V
      3 - GND
      4 - 14
      X - 15
      17- X  */

   tr_nSEL = 2,   /*5V*/
   tr_SCK = 3 ,   /*GND*/
   tr_NIRQ = 4,   tr_SDI = 14,
                  tr_FSK = 15,
   tr_CLK = 17




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
