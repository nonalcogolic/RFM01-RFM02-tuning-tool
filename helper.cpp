#include "helper.h"

#include "Commands/Receiver/configurationsetting.h"
#include "Commands/Receiver/receiversetting.h"
#include "Commands/Receiver/lowbatterydetectorandclockdivider.h"
#include "Commands/Receiver/outputandfifo.h"
#include "Commands/Receiver/datafilter.h"
#include "Commands/Receiver/afccontrol.h"
#include "Commands/Receiver/datafilter.h"

#include "qstring.h"


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

namespace Receiver
{

eFrequencyBand frequency(const QString & formValue)
{
   auto retValue = eFrequencyBand::fr_315;
   if (formValue == "433")
   {
      retValue = eFrequencyBand::fr_433;
   }
   else if (formValue == "868")
   {
      retValue = eFrequencyBand::fr_868;
   }
   else if (formValue == "915")
   {
      retValue = eFrequencyBand::fr_915;
   }
   return retValue;
}

eBaseband baseband(const QString & formValue)
{
   auto retValue = eBaseband::base_67;

   if (formValue == "134")
   {
      retValue = eBaseband::base_134;
   }
   else if (formValue == "200")
   {
      retValue = eBaseband::base_200;
   }
   else if (formValue == "270")
   {
      retValue = eBaseband::base_270;
   }
   else if (formValue == "340")
   {
      retValue = eBaseband::base_340;
   }
   else if (formValue == "400")
   {
      retValue = eBaseband::base_400;
   }
   else
   {
      //nothing
   }
   return retValue;
}

eVDIsignal vdiSignal(const QString & formValue)
{
   auto retValue = eVDIsignal::Digital_RSSI_Out;

   if (formValue == "Data Quality Detector (DQD)")
   {
      retValue = eVDIsignal::Data_Quality_Detector_Output;
   }
   else if (formValue == "Clock recovery lock")
   {
      retValue = eVDIsignal::Clock_Recovery_lock;
   }
   else if (formValue == "DRSSI && DQD")
   {
      retValue = eVDIsignal::DRSSI_DQD;
   }

   return retValue;
}

eLNAGain lnaGain(const QString & formValue)
{
   auto retValue = eLNAGain::lna_0;
   if (formValue == "14")
   {
      retValue = eLNAGain::lna_14;
   }
   else if (formValue == "6")
   {
      retValue = eLNAGain::lna_6;
   }
   else if (formValue == "20")
   {
      retValue = eLNAGain::lna_20;
   }

   return retValue;
}

eRSSI rssi(const QString & formValue)
{
   auto retValue = eRSSI::rssi_103;

   if (formValue == "97")
   {
      retValue = eRSSI::rssi_97;
   }
   else if (formValue == "91")
   {
      retValue = eRSSI::rssi_91;
   }
   else if (formValue == "85")
   {
      retValue = eRSSI::rssi_85;
   }
   else if (formValue == "79")
   {
      retValue = eRSSI::rssi_79;
   }
   else if (formValue == "73")
   {
      retValue = eRSSI::rssi_73;
   }

   return retValue;
}

eCLKfrequncy clk(const QString & formValue)
{
   auto retValue = eCLKfrequncy::clk_1;

   if (formValue == "1.25")
   {
      retValue = eCLKfrequncy::clk_1_25;
   }
   else if (formValue == "1.66")
   {
      retValue = eCLKfrequncy::clk_1_33;
   }
   else if (formValue == "2")
   {
      retValue = eCLKfrequncy::clk_2;
   }
   else if (formValue == "2.5")
   {
      retValue = eCLKfrequncy::clk_2_5;
   }
   else if (formValue == "3.33")
   {
      retValue = eCLKfrequncy::clk_3_33;
   }
   else if (formValue == "5")
   {
      retValue = eCLKfrequncy::clk_5;
   }
   else if (formValue == "10")
   {
      retValue = eCLKfrequncy::clk_10;
   }
   return retValue;
}

eFifoFillCondition fifoCondition(const QString & formValue)
{
   auto retValue = eFifoFillCondition::cond_VDI ;
   if (formValue == "Sync Word")
   {
      retValue = eFifoFillCondition::cond_sync_word ;
   }
   else if (formValue == "Always")
   {
      retValue = eFifoFillCondition::cond_Always ;
   }
   else if (formValue == "Reserved")
   {
      retValue = eFifoFillCondition::cond_reserved;
   }

   return retValue;
}

eRangeLimit rangeLimit(const QString & formValue)
{
   auto retValue = eRangeLimit::no_restriction;

   if (formValue == "+15/-16")
   {
      retValue = eRangeLimit::lim_pos15_neg16;
   }
   else if (formValue == "+7/-8")
   {
      retValue = eRangeLimit::lim_pos7_neg8;
   }
   else if (formValue == "+3/-4")
   {
      retValue = eRangeLimit::lim_pos3_neg4;
   }
   return retValue;
}

eAutomaticOperationMode automaticOperations(const QString & formValue)
{
   auto retValue = eAutomaticOperationMode::auto_mode_off;

   if (formValue == "Once")
   {
      retValue = eAutomaticOperationMode::run_once_after_powerUp;
   }
   else if (formValue == "Drop the F when VDI low")
   {
      retValue = eAutomaticOperationMode::drop_offset_when_VDI_low;
   }
   else if (formValue == "Keep independenly from VDI")
   {
      retValue = eAutomaticOperationMode::keep_offset_independently_from_VDI;
   }
   return retValue;
}

eDataFilterType filterType(const QString & formValue)
{
   auto retValue = eDataFilterType::OOK;

   if (formValue == "Digital")
   {
      retValue = eDataFilterType::DigitalFilter;
   }
   else if (formValue == "Analogue")
   {
      retValue = eDataFilterType::AnalogRC;
   }

   return retValue;
}

}


std::vector<bool> operator+(const std::vector<bool> & lhs, const std::vector<bool> & rhs)
{
   auto retValue = lhs;
   retValue.insert(retValue.end(), rhs.cbegin(), rhs.cend());
   return retValue;
}



