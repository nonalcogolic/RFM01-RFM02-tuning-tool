#include "receiversetting.h"


namespace Receiver
{

ReceiverSetting::ReceiverSetting()
   : ACommands(0xC0,0x00)
{}

void ReceiverSetting::setVDIsignal(const eVDIsignal signal)
{
   setValue(6, 2, signal);
}

void ReceiverSetting::setLNAgain(const eLNAGain gain)
{
   setValue(4, 2, gain);
}

void ReceiverSetting::setRSSI(const eRSSI rssi)
{
   setValue(1, 3, rssi);
}

void ReceiverSetting::enableWholeReceiverChain(const bool enabled)
{
   setValue(0, enabled);
}


}
