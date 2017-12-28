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
   template<class T>
   void setValue(const uint8_t offset, const uint8_t bitCount, const T value);

   void setValue(const uint8_t offset, const bool value);

private:
   void setValuel(const uint8_t offset, const uint8_t bitCount, const uint16_t value);

   tCMD mCmd;
};

template<class Enum>
void ACommands::setValue(const uint8_t offset, const uint8_t bitCount, const Enum value)
{
   setValuel(offset, bitCount, static_cast<uint16_t>(value));
}

#endif // ACOMMANDS_H
