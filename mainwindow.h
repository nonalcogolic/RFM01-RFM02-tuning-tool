#ifndef MainWindow_H
#define MainWindow_H

#include <QWidget>

#include "crmfhandler.h"
#include "crfmtransmitterhandler.h"
#include "CBroadcomPinout.h"
#include "cgpioevent.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

signals:
   void nIRQSignal(const bool state);
   void nIRQTransmitterSignal(const bool state);

public slots:
   void sendComand();
   void readStatus();
   void transmiiterSendComand();
   void readTrStatus();

   void nIRQ(const bool state);

   void sendAllRec();
   void sendAllTr();

   void sendData();

   void nIRQTransmitterFSK(const bool state); //transmition over FSK using PWR managment command 0xC039/0xC001

   void nIRQTransmitterSDI(const bool state); //Data transmit command 0xC6

private:   
   void sendDataFSK();
   void sendDataSDI();

   Ui::MainWindow *ui;
   CBroadcomPinout mPinout;
   CRMFHandler mReceiver;
   CRFMTransmitterHandler mTransmitterHandler;
   CGPIOEvent mEvents;

   bool transmitionIsOver;

};

#endif // MainWindow_H
