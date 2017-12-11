#include "crfmtransmitterhandler.h"


#include <chrono>
#include <thread>

namespace
{
void setPinDelay()
{
   const auto delay = std::chrono::nanoseconds(500);
   std::this_thread::sleep_for(delay);
}
}


CRFMTransmitterHandler::CRFMTransmitterHandler(IPinOut & pinout)
   : mPinout(pinout)
{
   mPinout.setPinDirrection(true, ePin::tr_nSEL);
   mPinout.setPinDirrection(true, ePin::tr_SDI);
   mPinout.setPinDirrection(true, ePin::tr_SCK);
   mPinout.setPinDirrection(false, ePin::tr_NIRQ);

   mPinout.setPinState(true, ePin::tr_nSEL);
   mPinout.setPinState(false, ePin::tr_SDI);
   mPinout.setPinState(true, ePin::tr_SCK);
}


void CRFMTransmitterHandler::sendComand(const std::vector<bool> command)
{
   mPinout.setPinState(false, ePin::tr_nSEL);

   for (auto bit : command)
   {
      mPinout.setPinState(bit, ePin::tr_SDI);
      mPinout.setPinState(true, ePin::tr_SCK);
      setPinDelay();
      mPinout.setPinState(false, ePin::tr_SCK);
   }

   mPinout.setPinState(true, ePin::tr_nSEL);
}

void CRFMTransmitterHandler::sendData(const std::vector<bool> command, const std::vector<bool> data)
{
   mPinout.setPinState(false, ePin::tr_nSEL);

   for (auto bit : command)
   {
      mPinout.setPinState(bit, ePin::tr_SDI);
      mPinout.setPinState(true, ePin::tr_SCK);
      setPinDelay();
      mPinout.setPinState(false, ePin::tr_SCK);
   }

   for (auto bit : data)
   {
      mPinout.setPinState(bit, ePin::tr_SDI);
      setPinDelay();
   }

   mPinout.setPinState(true, ePin::tr_nSEL);
}


std::vector<bool> CRFMTransmitterHandler::readStatus()
{
   std::vector<bool> output;

  // if (!mPinout.getPinState(ePin::nIRQ))
   {
       mPinout.setPinState(false, ePin::tr_nSEL);
       mPinout.setPinState(false, ePin::tr_SDI);

       //while (!mPinout.getPinState(ePin::nIRQ))
       auto command = std::vector<bool>{1,1,0,0,  1,1,0,0,  0,0,0,0,  0,0,0,0};

       for (int i = 0; i<16; ++i)
       {
          mPinout.setPinState(command[i], ePin::tr_SDI);
          mPinout.setPinState(true, ePin::tr_SCK);
          setPinDelay();

          if (i >= 8)
             output.push_back(mPinout.getPinState(ePin::tr_NIRQ));

          mPinout.setPinState(false, ePin::tr_SCK);
          setPinDelay();
       }

       mPinout.setPinState(true, ePin::tr_nSEL);
     //  mPinout.setPinState(true, ePin::SDI);
   }

   return output;
}
