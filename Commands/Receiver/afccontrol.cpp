#include "afccontrol.h"


namespace Receiver
{

AFCControl::AFCControl()
   : ACommands(0xC6,0x00)
{}

void AFCControl::setAutomaticOperationMode(const eAutomaticOperationMode mode)
{
   setValue(6, 2, mode);
}

void AFCControl::setRangeLimit(const eRangeLimit limit)
{
   setValue(4, 2, limit);
}

void AFCControl::enableStrobeEdge(const bool enabled)
{
   setValue(3, enabled);
}

void AFCControl::enableHighAccuracyMode(const bool enabled)
{
   setValue(2, enabled);
}

void AFCControl::enableFrequencyOffsetRegister(const bool enabled)
{
   setValue(1, enabled);
}

void AFCControl::enableAFCCalculations(const bool enabled)
{
   setValue(0, enabled);
}

}
