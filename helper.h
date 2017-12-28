#ifndef HELPER_H
#define HELPER_H

#include <vector>

#include <stdint.h>

enum class eEventType
{
   low,
   high,
   every, //TODO not supported yet
   rise,
   fall
};



namespace Helper
{
   std::vector<bool> convert(const int8_t byte);
   void setValue(const uint8_t offset, const uint8_t bitCount, const uint16_t value, std::vector<bool> & src);
}

std::vector<bool> operator+(const std::vector<bool> & lhs, const std::vector<bool> & rhs);

#endif // HELPER_H
