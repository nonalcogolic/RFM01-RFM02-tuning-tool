#ifndef CReceiverHandler_H
#define CReceiverHandler_H

#include "ipinout.h"

#include <vector>
#include <thread>

#include <QObject>

class CReceiverHandler : public QObject
{
    Q_OBJECT

public:
   CReceiverHandler(IPinOut & pinout);
   ~CReceiverHandler();

   void sendComand(const std::vector<bool> & command);

   std::vector<bool> readStatus();

   void startNIRQListenThread();

   void terminateNIRQListener();
private:
   IPinOut & mPinout;
};


#endif // CReceiverHandler_H
