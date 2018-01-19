#ifndef ReceiverControlPanel_H
#define ReceiverControlPanel_H

#include <QWidget>

#include "crmfhandler.h"

namespace Ui {
class ReceiverControlPanel;
}

class CBroadcomPinout;
class CGPIOEvent;
class ACommands;

class ReceiverControlPanel : public QWidget
{
   Q_OBJECT

public:
   explicit ReceiverControlPanel(CBroadcomPinout & pinout, CGPIOEvent & events, QWidget *parent = 0);
   ~ReceiverControlPanel();

signals:
   void nIRQSignal(const bool state);

private slots:
   void sendAll();
   void sendConfiguration();
   void sendFrequency();
   void sendReceiverSettings();
   void sendWakeUpTimer();
   void sendLowDutyCycle();
   void sendLowBattery();
   void sendAFC();
   void sendDataFilter();
   void sendDataRate();
   void sendFIFO();
   void sendResetMode();
   void sendReset();
   void sendReadstatus();


public slots:
   void receiver_nIRQ(const bool state);

private:
   void sendComand(const ACommands & cmd);

   Ui::ReceiverControlPanel *ui;

   CBroadcomPinout & mPinout;
   CGPIOEvent & mEvents;
   CRMFHandler mReceiver;

};

#endif // ReceiverControlPanel_H
