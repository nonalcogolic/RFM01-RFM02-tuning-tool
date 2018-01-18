#include "receivercontrolpanel.h"
#include "ui_receivercontrolpanel.h"

#include "CBroadcomPinout.h"
#include "cgpioevent.h"

#include <list>

#include <qmessagebox.h>
#include <qdebug.h>


ReceiverControlPanel::ReceiverControlPanel(CBroadcomPinout & pinout, CGPIOEvent & events, QWidget *parent)
   : QWidget(parent)
   , ui(new Ui::ReceiverControlPanel)
   , mPinout(pinout)
   , mEvents(events)
   , mReceiver(pinout)
{
   ui->setupUi(this);


   mEvents.listenPin(ePin::nIRQ, [this](const bool state) { emit nIRQSignal(state); }, eEventType::rise);
   connect(this, SIGNAL(nIRQSignal(const bool)), this, SLOT(receiver_nIRQ(const bool)), Qt::ConnectionType::QueuedConnection);


   connect(ui->pushButton_send_all , SIGNAL(clicked()), this, SLOT(sendAll()));
   connect(ui->pushButton_Configuration , SIGNAL(clicked()), this, SLOT(sendConfiguration()));
   connect(ui->pushButton_frequency , SIGNAL(clicked()), this, SLOT(sendFrequency()));
   connect(ui->pushButton_receiver_settings , SIGNAL(clicked()), this, SLOT(sendReceiverSettings()));
   connect(ui->pushButton_wakeUp , SIGNAL(clicked()), this, SLOT(sendWakeUpTimer()));
   connect(ui->pushButton_low_duty , SIGNAL(clicked()), this, SLOT(sendLowDutyCycle()));
   connect(ui->pushButton_bat_and_clk_rate , SIGNAL(clicked()), this, SLOT(sendLowBattery()));
   connect(ui->pushButton_AFC , SIGNAL(clicked()), this, SLOT(sendAFC()));
   connect(ui->pushButton_data_filter , SIGNAL(clicked()), this, SLOT(sendDataFilter()));
   connect(ui->pushButton_data_rate , SIGNAL(clicked()), this, SLOT(sendDataRate()));
   connect(ui->pushButton_fifo , SIGNAL(clicked()), this, SLOT(sendFIFO()));
   connect(ui->pushButton_reset_mode , SIGNAL(clicked()), this, SLOT(sendResetMode()));
   connect(ui->pushButton_SW_reset , SIGNAL(clicked()), this, SLOT(sendReset()));
   connect(ui->pushButton_read_status, SIGNAL(clicked()), this, SLOT(receiverReadStatus()));


   //ui->edit_multple_comand_rec->setText("0000 898A A7D0 C847 C69B C42A C200 C080 CE84 CE87 C081");

}

ReceiverControlPanel::~ReceiverControlPanel()
{
   delete ui;
}

void ReceiverControlPanel::sendComand(const std::vector<bool> & cmd)
{


   mReceiver.sendComand(cmd);
}

void ReceiverControlPanel::receiverReadStatus()
{
   auto word = mReceiver.readStatus();

   QString result;

   for (auto symb : word)
   {
      result += (symb) ? "1" : "0";
   }

   ui->lineEdit_status->setText(result);
}

void ReceiverControlPanel::receiver_nIRQ(const bool state)
{
   static int value= 0;
   value = (++value)%100;
   ui->progressBar->setValue(value);
}

void ReceiverControlPanel::sendAll()
{

}

void ReceiverControlPanel::sendConfiguration()
{

}

void ReceiverControlPanel::sendFrequency()
{

}

void ReceiverControlPanel::sendReceiverSettings()
{

}

void ReceiverControlPanel::sendWakeUpTimer()
{

}

void ReceiverControlPanel::sendLowDutyCycle()
{

}

void ReceiverControlPanel::sendLowBattery()
{

}

void ReceiverControlPanel::sendAFC()
{

}

void ReceiverControlPanel::sendDataFilter()
{

}

void ReceiverControlPanel::sendDataRate()
{

}

void ReceiverControlPanel::sendFIFO()
{

}

void ReceiverControlPanel::sendResetMode()
{

}

void ReceiverControlPanel::sendReset()
{

}

void ReceiverControlPanel::sendReadstatus()
{

}
