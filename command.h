#ifndef COMMAND_H
#define COMMAND_H

#include <vector>


using tCMD = std::vector<bool>;

namespace CMD
{
   const tCMD & CMD_SWITCH_ON_FSK_MODE();
   const tCMD & CMD_SWITCH_OFF();
   const tCMD & CMD_ENABLE_TX_SYNC();
   const tCMD & CMD_DISABLE_TX_SYNC();
   const tCMD & CMD_DATA_TRANSMIT();
   const tCMD & CMD_READ_STATUS();
}

#endif // COMMAND_H

