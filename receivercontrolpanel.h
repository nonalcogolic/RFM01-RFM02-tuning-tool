#ifndef ReceiverControlPanel_H
#define ReceiverControlPanel_H

#include <QWidget>

#include "creceiverhandler.h"

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
   void FIFO_interupt(const bool state);
   void VDI_interupt(const bool state);

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
   void quickConfig();


public slots:
   void receiver_nIRQ(const bool state);

   void receiver_FIFO_interupt(const bool state);
   void receiver_VDI_interupt(const bool state);

private:
   void restartFiFo();

   void sendComand(const ACommands & cmd);

   Ui::ReceiverControlPanel *ui;

   CBroadcomPinout & mPinout;
   CGPIOEvent & mEvents;
   CReceiverHandler mReceiver;

};

#endif // ReceiverControlPanel_H
