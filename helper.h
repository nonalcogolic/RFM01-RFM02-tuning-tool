#ifndef HELPER_H
#define HELPER_H

#include <vector>

#include <stdint.h>

class QString;


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

namespace Receiver
{
   enum class eFrequencyBand;
   enum class eBaseband;
   enum class eVDIsignal;
   enum class eLNAGain;
   enum class eRSSI;
   enum class eCLKfrequncy;
   enum class eFifoFillCondition;
   enum class eRangeLimit;
   enum class eAutomaticOperationMode;
   enum class eDataFilterType;

   eFrequencyBand frequency(const QString & formValue);
   eBaseband baseband(const QString & formValue);
   eVDIsignal vdiSignal(const QString & formValue);
   eLNAGain lnaGain(const QString & formValue);
   eRSSI rssi(const QString & formValue);
   eCLKfrequncy clk(const QString & formValue);
   eFifoFillCondition fifoCondition(const QString & formValue);
   eRangeLimit rangeLimit(const QString & formValue);
   eAutomaticOperationMode automaticOperations(const QString & formValue);
   eDataFilterType filterType(const QString & formValue);
}

std::vector<bool> operator+(const std::vector<bool> & lhs, const std::vector<bool> & rhs);

#endif // HELPER_H
