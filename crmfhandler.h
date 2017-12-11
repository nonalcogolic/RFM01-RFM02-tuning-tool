#ifndef CRMFHANDLER_H
#define CRMFHANDLER_H

#include "ipinout.h"

#include <vector>
#include <thread>

#include <QObject>

class CRMFHandler : public QObject
{
    Q_OBJECT

public:
   CRMFHandler(IPinOut & pinout);
   ~CRMFHandler();

   void sendComand(const std::vector<bool> command);

   std::vector<bool> readStatus();

   void startNIRQListenThread();

   void terminateNIRQListener();
private:
   IPinOut & mPinout;
};


#endif // CRMFHANDLER_H
