#ifndef RECEIVERSETTING_RECEIVER_H
#define RECEIVERSETTING_RECEIVER_H

#include "../ACommands.h"

namespace Receiver
{

enum class eVDIsignal
{
   Digital_RSSI_Out =0,
   Data_Quality_Detector_Output,
   Clock_Recovery_lock,
   DRSSI_DQD
};

enum class eLNAGain
{
   lna_0 = 0,
   lna_14 = 1,
   lna_6 = 2,
   lna_20 = 3
};

enum class eRSSI
{
   rssi_103,
   rssi_97,
   rssi_91,
   rssi_85,
   rssi_79,
   rssi_73
};

class ReceiverSetting : public ACommands
{
public:
   ReceiverSetting();

   void setVDIsignal(const eVDIsignal signal);
   void setLNAgain(const eLNAGain gain);
   void setRSSI(const eRSSI rssi);
   void enableWholeReceiverChain(const bool enabled);

};


}

#endif // RECEIVERSETTING_RECEIVER_H
