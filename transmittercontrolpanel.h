#ifndef TRANSMITTERCONTROLPANEL_H
#define TRANSMITTERCONTROLPANEL_H

#include <QWidget>

class ACommands;

namespace Ui {
class TransmitterControlPanel;
}

class TransmitterControlPanel : public QWidget
{
   Q_OBJECT

public:
   explicit TransmitterControlPanel(QWidget *parent = 0);
   ~TransmitterControlPanel();


signals:
   void startDataTransmittion(const bool throughTheFSK, const std::vector<bool> command);
   void sendCommand(const std::vector<bool> command);
   void readStatus(const std::vector<bool> readstatusCMD);

public slots:
   void dataTransmitionFinished(const bool throughTheFSK);
   void statusReceived(const QString & data);

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

private:
   void send(const ACommands & cmd);

   Ui::TransmitterControlPanel *ui;
};

#endif // TRANSMITTERCONTROLPANEL_H
