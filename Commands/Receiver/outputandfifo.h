#ifndef OUTPUTANDFIFO_H
#define OUTPUTANDFIFO_H

#include "../ACommands.h"

namespace Receiver
{

class OutputAndFIFO : public ACommands
{
public:
   OutputAndFIFO();

   enum class eFifoFillCondition
   {
      cond_VDI = 0,
      cond_sync_word = 1,
      cond_Always = 3
   };

   void setFIFOitLevel(const int8_t bits); //8 max
   void setFIFOFillCondition(const eFifoFillCondition condition);
   void enableFifoFill(const bool enabled);
   void enableFIFO(const bool enabled);

};


}

#endif // OUTPUTANDFIFO_H
