#ifndef MainWindow_H
#define MainWindow_H

#include <QWidget>

#include "crmfhandler.h"
#include "crfmtransmitterhandler.h"
#include "CBroadcomPinout.h"
#include "cgpioevent.h"
#include "transmittercontrolpanel.h"

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

   void dataTransmitionFinished(const bool throughFSK);
   void transmitterStatusChanged(const QString & data);

public slots:
   void receiverSendComand(const std::vector<bool> & cmd);
   void receiverReadStatus();

   void transmiiterSendCommand(const std::vector<bool> & cmd);
   void readTrStatus(const std::vector<bool> & readstatusCMD);

   void nIRQ(const bool state);

   void sendData(const bool throughFSK, const std::vector<bool> transmitDataSDIcmd);

   void nIRQTransmitterFSK(const bool state); //transmition over FSK using PWR managment command 0xC039/0xC001

   void nIRQTransmitterSDI(const bool state); //Data transmit command 0xC6

private:   
   void sendDataFSK();
   void sendDataSDI(const std::vector<bool> transmitDataSDIcmd);

   Ui::MainWindow *ui;
   CBroadcomPinout mPinout;
   CRMFHandler mReceiver;
   CRFMTransmitterHandler mTransmitterHandler;
   CGPIOEvent mEvents;
   TransmitterControlPanel trControlPanel;

   bool transmitionIsOver;

};

#endif // MainWindow_H
