#include "ACommands.h"
#include "../helper.h"

ACommands::ACommands(const uint8_t & cmd)
   : mCmd(Helper::convert(cmd))
{

}

ACommands::ACommands(const uint8_t & cmd_pt1, const uint8_t & cmd_pt2)
   : mCmd(Helper::convert(cmd_pt1) + Helper::convert(cmd_pt2))
{

}

tCMD ACommands::operator()() const
{
   return mCmd;
}

void ACommands::setValuel(const uint8_t offset, const uint8_t bitCount, const uint16_t value)
{
   Helper::setValue(offset, bitCount, value, mCmd);
}

void ACommands::setValue(const uint8_t offset, const bool value)
{
   Helper::setValue(offset, 1, (value ? 1 : 0) , mCmd);
}
