#ifndef RESETMODE_RECEIVER_H
#define RESETMODE_RECEIVER_H

#include "../ACommands.h"

namespace Receiver
{

class ResetMode : public ACommands
{
public:
   ResetMode();
   
   void disableHighlySensetiveResetMode(const bool disable);
};


}

#endif // RESETMODE_RECEIVER_H
