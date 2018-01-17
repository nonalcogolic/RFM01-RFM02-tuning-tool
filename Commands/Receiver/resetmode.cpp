#include "resetmode.h"


namespace Receiver
{

ResetMode::ResetMode()
   : ACommands(0xDA,0x00)
{}

void ResetMode::disableHighlySensetiveResetMode(const bool disable)
{
   setValue(0, disable);
}

}
