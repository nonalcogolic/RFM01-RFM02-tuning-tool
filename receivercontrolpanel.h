#ifndef ReceiverControlPanel_H
#define ReceiverControlPanel_H

#include <QWidget>

#include "crmfhandler.h"

namespace Ui {
class ReceiverControlPanel;
}

class CBroadcomPinout;
class CGPIOEvent;

class ReceiverControlPanel : public QWidget
{
   Q_OBJECT

public:
   explicit ReceiverControlPanel(CBroadcomPinout & pinout, CGPIOEvent & events, QWidget *parent = 0);
   ~ReceiverControlPanel();

signals:
   void nIRQSignal(const bool state);

public slots:
   void receiverSendComand(const std::vector<bool> & cmd);
   void receiverReadStatus();   
   void receiver_nIRQ(const bool state);

private:
   Ui::ReceiverControlPanel *ui;

   CBroadcomPinout & mPinout;
   CGPIOEvent & mEvents;
   CRMFHandler mReceiver;

};

#endif // ReceiverControlPanel_H
