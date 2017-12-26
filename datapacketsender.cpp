#include "datapacketsender.h"
#include "ipinout.h"

DataPacketSender::DataPacketSender(IPinOut & pinout, const ePin usedPin, const std::vector<bool> & data)
   : mPinout(pinout)
   , mData(data)
   , mCursor(0)
   , mSize(data.size())
   , mUsedPin(usedPin)
{}

bool DataPacketSender::eof() const
{
   return mCursor == mSize;
}

bool DataPacketSender::sendNext()
{
   if (!eof())
   {
      mPinout.setPinStateForce(mData[mCursor], mUsedPin);
      ++mCursor;
   }
   return mCursor < mSize;
}

void DataPacketSender::reset()
{
   mCursor = 0;
}
