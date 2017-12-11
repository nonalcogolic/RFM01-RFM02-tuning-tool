#ifndef CRFMTRANSMITTERHANDLER_H
#define CRFMTRANSMITTERHANDLER_H

#include "ipinout.h"

#include <vector>

class CRFMTransmitterHandler
{
public:
   CRFMTransmitterHandler(IPinOut & pinout);

   void sendComand(const std::vector<bool> command);
   void sendData(const std::vector<bool> command, const std::vector<bool> data);

   std::vector<bool>  readStatus();

private:
   IPinOut & mPinout;
};

#endif // CRFMTRANSMITTERHANDLER_H
