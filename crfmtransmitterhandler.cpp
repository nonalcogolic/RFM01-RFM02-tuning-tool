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
   mPinout.setPinDirrection(false, ePin::tr_NIRQ);

   mPinout.setPinState(true, ePin::tr_nSEL);
   mPinout.setPinState(false, ePin::tr_SDI);
   mPinout.setPinState(true, ePin::tr_SCK);
   mPinout.setPinState(false, ePin::tr_NIRQ);
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
void CRFMTransmitterHandler::sendData(const std::vector<bool> & command, const std::vector<bool> data)
//--------------------------------------------------
{
   mPinout.setPinState(false, ePin::tr_nSEL);

   for (auto bit : command)
   {
      mPinout.setPinState(bit, ePin::tr_SDI);
      mPinout.setPinState(true, ePin::tr_SCK);
      mPinout.setPinState(false, ePin::tr_SCK);
   }

   for (auto bit : data)
   {
      mPinout.setPinState(bit, ePin::tr_SDI);
   }

   mPinout.setPinState(true, ePin::tr_SCK);
   mPinout.setPinState(true, ePin::tr_nSEL);
}

//--------------------------------------------------
void CRFMTransmitterHandler::sendDataFSK()
//--------------------------------------------------
{
   qDebug() << "CRFMTransmitterHandler::sendDataFSK Starting data transmition";
   mDataSender.reset();
   mDataSender.setUsedPin(ePin::tr_FSK);
   sendComand(CMD::CMD_ENABLE_TX_SYNC());
   sendComand(CMD::CMD_SWITCH_ON_FSK_MODE());
}

//--------------------------------------------------
void CRFMTransmitterHandler::sendDataSDI()
//--------------------------------------------------
{
   qDebug() << "CRFMTransmitterHandler::sendDataSDI Starting data transmition";
   mDataSender.reset();
   mDataSender.setUsedPin(ePin::tr_SDI);
   sendComand(CMD::CMD_ENABLE_TX_SYNC());

   const auto & command = CMD::CMD_DATA_TRANSMIT();

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
   mPinout.setPinState(true, ePin::tr_SCK); //TODO: order?
   mPinout.setPinState(true, ePin::tr_nSEL);
   sendComand(CMD::CMD_DISABLE_TX_SYNC());
}

//--------------------------------------------------
std::vector<bool> CRFMTransmitterHandler::readStatus()
//--------------------------------------------------
{
   std::vector<bool> output;

   mPinout.setPinState(false, ePin::tr_nSEL);
   mPinout.setPinState(false, ePin::tr_SDI);

   auto & command = CMD::CMD_READ_STATUS();

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
   sendComand(CMD::CMD_SWITCH_OFF());
   sendComand(CMD::CMD_DISABLE_TX_SYNC());
}
