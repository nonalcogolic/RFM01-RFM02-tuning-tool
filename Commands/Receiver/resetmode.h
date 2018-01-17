#ifndef RESETMODE_H
#define RESETMODE_H

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

#endif // RESETMODE_H
