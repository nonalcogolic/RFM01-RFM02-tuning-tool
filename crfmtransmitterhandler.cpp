#include "crfmtransmitterhandler.h"
#include "helper.h"
#include "command.h"

#include "qdebug.h"

#include <chrono>

const auto data
   = Helper::convert(0xAA)
   + Helper::convert(0xAA)
   + Helper::convert(0xAA)
   + Helper::convert(0x2D)
   + Helper::convert(0xD4)
//   + Helper::convert(0xCC)
   + Helper::convert(0xCC);
 //  + Helper::convert(0xAA);

//--------------------------------------------------
CRFMTransmitterHandler::CRFMTransmitterHandler(IPinOut & pinout)
   : mPinout(pinout)
   , mDataSender(pinout, data)
//--------------------------------------------------
{
   mPinout.setPinDirrection(true, ePin::tr_nSEL);
   mPinout.setPinDirrection(true, ePin::tr_SDI);
   mPinout.setPinDirrection(true, ePin::tr_SCK);
   mPinout.setPinDirrection(true, ePin::tr_FSK);
   mPinout.setPinDirrection(false, ePin::tr_NIRQ);

   mPinout.setPinState(true, ePin::tr_nSEL);
   mPinout.setPinState(false, ePin::tr_SDI);
   mPinout.setPinState(true, ePin::tr_SCK);
   mPinout.setPinState(false, ePin::tr_NIRQ);   
   mPinout.setPinState(false, ePin::tr_FSK);
}

//--------------------------------------------------
void CRFMTransmitterHandler::sendComand(const std::vector<bool> & command)
//--------------------------------------------------
{
   mPinout.setPinState(false, ePin::tr_nSEL);

   for (auto bit : command)
   {
      mPinout.setPinState(bit, ePin::tr_SDI);
      mPinout.setPinState(true, ePin::tr_SCK);
      mPinout.setPinState(false, ePin::tr_SCK);
   }

   mPinout.setPinState(true, ePin::tr_nSEL);
}

//--------------------------------------------------
void CRFMTransmitterHandler::sendDataFSK()
//--------------------------------------------------
{
   qDebug() << "CRFMTransmitterHandler::sendDataFSK Starting data transmition";
   mDataSender.reset();
   mDataSender.setUsedPin(ePin::tr_FSK);
}

//--------------------------------------------------
void CRFMTransmitterHandler::sendDataSDI(const std::vector<bool> & command)
//--------------------------------------------------
{
   qDebug() << "CRFMTransmitterHandler::sendDataSDI Starting data transmition";
   mDataSender.reset();
   mDataSender.setUsedPin(ePin::tr_SDI);

   mPinout.setPinState(false, ePin::tr_SCK); //TODO: check if it is a reason of trouble
   mPinout.setPinState(false, ePin::tr_nSEL);

   for (auto bit : command)
   {
      mPinout.setPinState(bit, ePin::tr_SDI);
      mPinout.setPinState(true, ePin::tr_SCK);
      mPinout.setPinState(false, ePin::tr_SCK);
   }
}

//--------------------------------------------------
void CRFMTransmitterHandler::stopSendDataSDI()
//--------------------------------------------------
{   
   mPinout.setPinState(true, ePin::tr_nSEL);
   mPinout.setPinState(true, ePin::tr_SCK); //TODO: no need I guess and may be reason of bugs. Remove and check workability
   qDebug() << "CRFMTransmitterHandler::stopSendDataSDI";
}

//--------------------------------------------------
std::vector<bool> CRFMTransmitterHandler::readStatus(const std::vector<bool> command)
//--------------------------------------------------
{
   std::vector<bool> output;

   mPinout.setPinState(false, ePin::tr_nSEL);
   mPinout.setPinState(false, ePin::tr_SDI);

   for (int i = 0; i<8; ++i)
   {
      mPinout.setPinState(command[i], ePin::tr_SDI);
      mPinout.setPinState(true, ePin::tr_SCK);
      mPinout.setPinState(false, ePin::tr_SCK);
   }

   for (int i = 0; i<7; ++i)
   {
      output.push_back(mPinout.getPinState(ePin::tr_NIRQ));
      mPinout.setPinState(true, ePin::tr_SCK);
      mPinout.setPinState(false, ePin::tr_SCK);
   }
   output.push_back(mPinout.getPinState(ePin::tr_NIRQ));

   mPinout.setPinState(true, ePin::tr_SDI);
   mPinout.setPinState(true, ePin::tr_nSEL);

   return output;
}

//--------------------------------------------------
bool CRFMTransmitterHandler::bitSyncArived()
//--------------------------------------------------
{
   static auto latest = std::chrono::system_clock::now();
   auto currentTime = std::chrono::system_clock::now();
   qDebug() <<" bit sent" << std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime-latest).count();
   latest = currentTime;

   return mDataSender.sendNext();
}

//--------------------------------------------------
void CRFMTransmitterHandler::stopSendDataFSK()
//--------------------------------------------------
{
   //No need
}
