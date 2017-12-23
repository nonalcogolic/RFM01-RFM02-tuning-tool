#include "datapacketsender.h"
#include "IPinOut.h"

DataPacketSender::DataPacketSender(IPinOut & pinout, const std::vector<bool> &data)
   : mPinout(pinout)
   , mData(data)
   , mCursor(0)
{}

bool DataPacketSender::eof() const
{
   return mCursor == mData.size();
}

void DataPacketSender::sendNext()
{
   if (!eof())
   {
      mPinout.setPinState(mData[mCursor], ePin::tr_NIRQ);
      ++mCursor;
   }
}

void DataPacketSender::reset()
{
   mCursor = 0;
}
