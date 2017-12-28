#include "helper.h"



std::vector<bool> Helper::convert(const int8_t byte)
{
   std::vector<bool> retValue;
   for (unsigned char i = 0x80; i != 0 ; i >>= 1)
   {
      retValue.push_back( i & byte);
   }
   return retValue;
}

void Helper::setValue(const uint8_t offset, const uint8_t bitCount, const uint16_t value, std::vector<bool> & src)
{
   uint16_t start = 0x01;
   const uint8_t reversStart = src.size() - (1 + offset);
   for (auto i = 0 ; i < bitCount; ++i)
   {
      const int8_t index = reversStart - i;
      src[index] = value & (1 << i);
   }
}

std::vector<bool> operator+(const std::vector<bool> & lhs, const std::vector<bool> & rhs)
{
   auto retValue = lhs;
   retValue.insert(retValue.end(), rhs.cbegin(), rhs.cend());
   return retValue;
}



