#include "datafilter.h"


namespace Receiver
{

DataFilter::DataFilter()
   : ACommands(0xC4,0x20)
{}

void DataFilter::enableAutoClockRecovery(const bool enabled)
{
   setValue(7, enabled);
}

void DataFilter::onClockRecovery(const bool active)
{
   setValue(6, active);
}

void DataFilter::setDataFilterType(const eDataFilterType type)
{
   setValue(3, 2, type);
}

void DataFilter::setDQDparams(const int8_t value)
{
   setValue(0, 3, value);
}

}
