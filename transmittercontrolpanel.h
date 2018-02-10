#ifndef TRANSMITTERCONTROLPANEL_H
#define TRANSMITTERCONTROLPANEL_H

#include <QWidget>
#include "crfmtransmitterhandler.h"

class ACommands;
class CBroadcomPinout;
class CGPIOEvent;

namespace Ui {
class TransmitterControlPanel;
}

class TransmitterControlPanel : public QWidget
{
   Q_OBJECT

public:
   explicit TransmitterControlPanel(CBroadcomPinout & pinout, CGPIOEvent & events, QWidget *parent = 0);
   ~TransmitterControlPanel();

signals:
   void nIRQTransmitterSignal(const bool state);

private slots:
   void sendAll();
   void sendConfig();
   void sendPowerManagment();
   void sendFrequency();
   void sendDataRate();
   void sendPowerSettings();
   void sendTXandTreshold();
   void sendSleep();
   void sendWakeUpTime();
   void sendDataTransmit();
   void sendReadStatus();
   void sendPLLSettings();
   void sendHWReset();

private slots:
   void nIRQTransmitterFSK(const bool state); //transmition over FSK using PWR managment command 0xC039/0xC001
   void nIRQTransmitterSDI(const bool state); //Data transmit command 0xC6

private:
   void sendDataFSK();
   void sendDataSDI(const std::vector<bool> transmitDataSDIcmd);
   void sendData(const bool throughFSK, const std::vector<bool> transmitDataSDIcmd);
   void dataTransmitionFinished(const bool throughTheFSK);

private:
   void send(const ACommands & cmd);

   Ui::TransmitterControlPanel *ui;

   CBroadcomPinout & mPinout;
   CGPIOEvent & mEvents;
   CRFMTransmitterHandler mTransmitterHandler;
};

#endif // TRANSMITTERCONTROLPANEL_H
