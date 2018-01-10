#ifndef TRANSMITTERCONTROLPANEL_H
#define TRANSMITTERCONTROLPANEL_H

#include <QWidget>

namespace Ui {
class TransmitterControlPanel;
}

class TransmitterControlPanel : public QWidget
{
   Q_OBJECT

public:
   explicit TransmitterControlPanel(QWidget *parent = 0);
   ~TransmitterControlPanel();

public slots:
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
   Ui::TransmitterControlPanel *ui;
};

#endif // TRANSMITTERCONTROLPANEL_H
