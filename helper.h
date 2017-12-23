#ifndef HELPER_H
#define HELPER_H

#include <vector>


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
   std::vector<bool> convert(const unsigned char byte);
}

std::vector<bool> operator+(const std::vector<bool> & lhs, const std::vector<bool> & rhs);

#endif // HELPER_H
