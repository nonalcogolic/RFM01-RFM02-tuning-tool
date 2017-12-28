#include "command.h"


#include "helper.h"

namespace Ncmd
{
   const tCMD CMD_SWITCH_ON_FSK_MODE = Helper::convert(0xC0) + Helper::convert(0x39);
   const tCMD CMD_SWITCH_OFF =  Helper::convert(0xC0) + Helper::convert(0x01);
   const tCMD CMD_ENABLE_TX_SYNC = Helper::convert(0xC0) + Helper::convert(0x39);
   const tCMD CMD_DISABLE_TX_SYNC = Helper::convert(0xC0) + Helper::convert(0x39);
   const tCMD CMD_DATA_TRANSMIT = Helper::convert(0xC6);
   const tCMD CMD_READ_STATUS = Helper::convert(0xCC);
}



namespace CMD
{

const tCMD & CMD_SWITCH_ON_FSK_MODE()
{
   return Ncmd::CMD_SWITCH_ON_FSK_MODE;
}

const tCMD & CMD_SWITCH_OFF()
{
   return Ncmd::CMD_SWITCH_OFF;
}

const tCMD & CMD_ENABLE_TX_SYNC()
{
   return Ncmd::CMD_ENABLE_TX_SYNC;
}

const tCMD & CMD_DISABLE_TX_SYNC()
{
   return Ncmd::CMD_DISABLE_TX_SYNC;
}

const tCMD & CMD_DATA_TRANSMIT()
{
   return Ncmd::CMD_DATA_TRANSMIT;
}

const tCMD & CMD_READ_STATUS()
{
   return Ncmd::CMD_READ_STATUS;
}


}

