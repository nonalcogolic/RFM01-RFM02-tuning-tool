#include "transmittercontrolpanel.h"
#include "ui_transmittercontrolpanel.h"

TransmitterControlPanel::TransmitterControlPanel(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::TransmitterControlPanel)
{
   ui->setupUi(this);
}

TransmitterControlPanel::~TransmitterControlPanel()
{
   delete ui;

   connect(ui->but_send_all, SIGNAL(clicked()), this, SLOT(sendAll()));
   connect(ui->but_send_conf, SIGNAL(clicked()), this, SLOT(sendConfig()));
   connect(ui->but_send_pow_man, SIGNAL(clicked()), this, SLOT(sendPowerManagment()));
   connect(ui->but_send_work_freq, SIGNAL(clicked()), this, SLOT(sendFrequency()));
   connect(ui->but_send_datarate, SIGNAL(clicked()), this, SLOT(sendDataRate()));
   connect(ui->but_send_pow, SIGNAL(clicked()), this, SLOT(sendPowerSettings()));
   connect(ui->but_send_tx_dwake_treshold, SIGNAL(clicked()), this, SLOT(sendTXandTreshold()));
   connect(ui->but_send_sleep, SIGNAL(clicked()), this, SLOT(sendSleep()));
   connect(ui->but_send_wake, SIGNAL(clicked()), this, SLOT(sendWakeUpTime()));
   connect(ui->but_transmit_data, SIGNAL(clicked()), this, SLOT(sendDataTransmit()));
   connect(ui->but_read_status, SIGNAL(clicked()), this, SLOT(sendReadStatus()));
   connect(ui->but_send_pll, SIGNAL(clicked()), this, SLOT(sendPLLSettings()));

}

void TransmitterControlPanel::sendAll()
{

}

void TransmitterControlPanel::sendConfig()
{

}

void TransmitterControlPanel::sendPowerManagment()
{

}

void TransmitterControlPanel::sendFrequency()
{

}

void TransmitterControlPanel::sendDataRate()
{

}

void TransmitterControlPanel::sendPowerSettings()
{

}

void TransmitterControlPanel::sendTXandTreshold()
{

}

void TransmitterControlPanel::sendSleep()
{

}

void TransmitterControlPanel::sendWakeUpTime()
{

}

void TransmitterControlPanel::sendDataTransmit()
{

}

void TransmitterControlPanel::sendReadStatus()
{

}

void TransmitterControlPanel::sendPLLSettings()
{

}
