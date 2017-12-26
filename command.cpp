#include "command.h"


#include "helper.h"

namespace CMD
{

const tCMD CMD_SWITCH_ON_FSK_MODE()
{
   return Helper::convert(0xC0) + Helper::convert(0x39);
}

const tCMD CMD_SWITCH_OFF()
{
   return Helper::convert(0xC0) + Helper::convert(0x01);
}

const tCMD CMD_ENABLE_TX_SYNC()
{
   return Helper::convert(0xC2) + Helper::convert(0x20);
}

const tCMD CMD_DISABLE_TX_SYNC()
{
   return Helper::convert(0xC2) + Helper::convert(0x00);
}

const tCMD CMD_DATA_TRANSMIT()
{
   return Helper::convert(0xC6);
}

}

