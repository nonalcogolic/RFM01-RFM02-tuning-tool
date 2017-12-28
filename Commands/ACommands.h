#ifndef ACOMMANDS_H
#define ACOMMANDS_H

#include <vector>
#include <stdint.h>

using tCMD = std::vector<bool>;

class ACommands
{
public:
   ACommands(const uint8_t & cmd);
   ACommands(const uint8_t & cmd_pt1, const uint8_t & cmd_pt2);

   tCMD operator()();
protected:
   void setValue(const uint8_t offset, const uint8_t bitCount, const uint16_t value);

   tCMD mCmd;
};

#endif // ACOMMANDS_H
