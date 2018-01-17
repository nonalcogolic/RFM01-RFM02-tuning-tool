#include "outputandfifo.h"


namespace Receiver
{

OutputAndFIFO::OutputAndFIFO()
   : ACommands(0xCE,0x00)
{}

void OutputAndFIFO::setFIFOitLevel(const int8_t bits) //8 max
{
   setValue(4, 4, bits);
}

void OutputAndFIFO::setFIFOFillCondition(const eFifoFillCondition condition)
{
  setValue(2, 2, condition);
}

void OutputAndFIFO::enableFifoFill(const bool enabled)
{
   setValue(1, enabled);
}

void OutputAndFIFO::enableFIFO(const bool enabled)
{
   setValue(0, enabled);
}

}
