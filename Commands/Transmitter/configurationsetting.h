#ifndef CONFIGURATIONSETTING_H
#define CONFIGURATIONSETTING_H

#include "../ACommands.h"

namespace NTransmitter
{

class ConfigurationSetting : public ACommands
{
public:
   ConfigurationSetting();

   enum class eFrequency
   {
      fr_433 = 1,
      fr_868,
      fr_915
   };
   enum class eClockFrequency
   {
      clk_1,
      clk_1_25,
      clk_1_66,
      clk_2,
      clk_2_5,
      clk_3_33,
      clk_5,
      clk_10
   };
   enum class eBandwidth_khz
   {
      bw_30 = 0,
      bw_60,
      bw_90,
      bw_120,
      bw_150,
      bw_180,
      bw_210
   };

   void setFrequency(const eFrequency freq = eFrequency::fr_433);
   void setClkFrequency(const eClockFrequency freq = eClockFrequency::clk_1);
   void setClkFrequency(const int freqDevider);

   void setCrystalLoadCapasitance(const int8_t pf); //8.5-15.5  Scale: 1/10, to set 8.5 value equal 85 should be used

   void setOutputBandwidth(const eBandwidth_khz bandwidth = eBandwidth_khz::bw_30);
   void setOutputBandwidth(const int value);
   void setBandwidthSign(const bool positive);

};

}

#endif // CONFIGURATIONSETTING_H
