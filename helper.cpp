#include "helper.h"



std::vector<bool> Helper::convert(const unsigned char byte)
{
   std::vector<bool> retValue;
   for (unsigned char i = 0x80; i != 0 ; i >>= 1)
   {
      retValue.push_back( i & byte);
   }
   return retValue;
}


std::vector<bool> operator+(const std::vector<bool> & lhs, const std::vector<bool> & rhs)
{
   auto retValue = lhs;
   retValue.insert(retValue.end(), rhs.cbegin(), rhs.cend());
   return retValue;
}
