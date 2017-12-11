#include "crmfhandler.h"

#include <chrono>

void setPinDelay()
{
   const auto delay = std::chrono::microseconds(1);
   std::this_thread::sleep_for(delay);
}


CRMFHandler::CRMFHandler(IPinOut & pinout)
   : QObject(nullptr)
   , mPinout(pinout)
{
   mPinout.setPinState(true, ePin::nSel);
   mPinout.setPinState(false, ePin::SDI);
   mPinout.setPinState(true, ePin::SCK);

}

CRMFHandler::~CRMFHandler()
{
}


void CRMFHandler::sendComand(const std::vector<bool> command)
{
   mPinout.setPinState(false, ePin::SDI);
   mPinout.setPinState(false, ePin::nSel);

   for (auto bit : command)
   {
      mPinout.setPinState(bit, ePin::SDI);
      mPinout.setPinState(true, ePin::SCK);
      setPinDelay();
      mPinout.setPinState(false, ePin::SCK);
   }

   mPinout.setPinState(true, ePin::nSel);
}

std::vector<bool> CRMFHandler::readStatus()
{
   std::vector<bool> output;

  // if (!mPinout.getPinState(ePin::nIRQ))
   {
       mPinout.setPinState(false, ePin::nSel);
       mPinout.setPinState(false, ePin::SDI);

       //while (!mPinout.getPinState(ePin::nIRQ))
       for (int i = 0; i<16; ++i)
       {
          mPinout.setPinState(true, ePin::SCK);
          setPinDelay();
          output.push_back(mPinout.getPinState(ePin::SDO));
          mPinout.setPinState(false, ePin::SCK);
       }

       mPinout.setPinState(true, ePin::nSel);
     //  mPinout.setPinState(true, ePin::SDI);
   }

   return output;
}
