#ifndef CRFMTRANSMITTERHANDLER_H
#define CRFMTRANSMITTERHANDLER_H

#include "ipinout.h"
#include "datapacketsender.h"

#include <vector>

class CRFMTransmitterHandler
{
public:
   CRFMTransmitterHandler(IPinOut & pinout);

   void sendComand(const std::vector<bool> command);
   void sendData(const std::vector<bool> command, const std::vector<bool> data);

   void sendDataFSK();
   void sendDataSDI();
   std::vector<bool> readStatus();

   bool bitSyncArived();

private:
   IPinOut & mPinout;
   DataPacketSender mDataSender;
};

#endif // CRFMTRANSMITTERHANDLER_H
