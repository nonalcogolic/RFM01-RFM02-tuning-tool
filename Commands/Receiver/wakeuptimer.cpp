#include "wakeuptimer.h"


namespace Receiver
{

WakeUpTimer::WakeUpTimer()
   : ACommands(0xE0,0x00)
{}

void WakeUpTimer::setPeriod(const uint8_t mantis, const uint8_t order)
{
   const auto cutOrder = 0x1F & order;
   setValue(8, 5, cutOrder);
   setValue(0, 8, mantis);
}

}
