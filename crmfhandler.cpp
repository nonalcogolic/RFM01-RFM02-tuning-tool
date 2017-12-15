#include "crmfhandler.h"


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

void CRMFHandler::sendComand(const std::vector<bool> & command)
{
   mPinout.setPinState(false, ePin::nSel);

   for (auto bit : command)
   {
      mPinout.setPinState(bit, ePin::SDI);
      mPinout.setPinState(true, ePin::SCK);
      mPinout.setPinState(false, ePin::SCK);
   }

   mPinout.setPinState(true, ePin::SDI);
   mPinout.setPinState(true, ePin::nSel);
}

std::vector<bool> CRMFHandler::readStatus()
{
   std::vector<bool> output;

   mPinout.setPinState(false, ePin::nSel);
   mPinout.setPinState(false, ePin::SDI);

   for (int i = 0; i<16; ++i)
   {
      mPinout.setPinState(true, ePin::SCK);
      output.push_back(mPinout.getPinState(ePin::SDO));
      mPinout.setPinState(false, ePin::SCK);
   }

   for (int i = 0; i<8; ++i)
   {
      mPinout.setPinState(true, ePin::SCK);
      output.push_back(mPinout.getPinState(ePin::SDO));
      mPinout.setPinState(false, ePin::SCK);
   }

   mPinout.setPinState(true, ePin::nSel);


   return output;
}
