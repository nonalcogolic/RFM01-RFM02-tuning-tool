#include "sleep.h"

Sleep::Sleep()
   : ACommands(0xC4, 0x00)
{}

void Sleep::setSleepAfter(const uint8_t delayTicks)
{
   setValue(0, 8, delayTicks);
}
