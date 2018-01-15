#ifndef AFCCONTROL_H
#define AFCCONTROL_H

#include "../ACommands.h"

namespace Receiver
{

class AFCControl : public ACommands
{
public:
   AFCControl();

   enum class eAutomaticOperationMode
   {
      auto_mode_off,
      run_once_after_powerUp,
      drop_offset_when_VDI_low,
      keep_offset_independently_from_VDI
   };

   enum class eRangeLimit
   {
      no_restriction,
      lim_pos15_neg16,
      lim_pos7_neg8,
      lim_pos3_neg4
   };

   void setAutomaticOperationMode(const eAutomaticOperationMode mode);
   void setRangeLimit(const eRangeLimit limit);
   void enableStrobeEdge(const bool enabled);
   void enableHighAccuracyMode(const bool enabled);
   void enableFrequencyOffsetRegister(const bool enabled);
   void enableAFCCalculations(const bool enabled);

};


}

#endif // AFCCONTROL_H
