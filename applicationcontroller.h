#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H


#include <QObject>

#include "receivercontrolpanel.h"
#include "transmittercontrolpanel.h"

#include "creceiverhandler.h"
#include "crfmtransmitterhandler.h"
#include "CBroadcomPinout.h"
#include "cgpioevent.h"


class ApplicationController : public QObject
{
   Q_OBJECT
public:
   explicit ApplicationController(QObject *parent = nullptr);

signals:

public slots:


private:
   CBroadcomPinout mPinout;
   CGPIOEvent mEvents;

   ReceiverControlPanel mReceiverPanel;
   TransmitterControlPanel mTransmitterPanel;
};

#endif // APPLICATIONCONTROLLER_H
