#ifndef DATAPACKETSENDER_H
#define DATAPACKETSENDER_H

#include <vector>
#include <inttypes.h>

class IPinOut;
class DataPacketSender
{
public:
   /*
    * @data param is the sequence of 0 and 1
    */
   DataPacketSender(IPinOut & pinout, const std::vector<bool> & data);

   bool eof() const;
   void sendNext();
   void reset();

private:
   IPinOut & mPinout;
   const std::vector<bool> mData;
   size_t mCursor;
};

#endif // DATAPACKETSENDER_H
