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
   connect(ui->pushButton_read_status, SIGNAL(clicked()), this, SLOT(receiverReadStatus()));

   mEvents.listenPin(ePin::nIRQ, [this](const bool state) { emit nIRQSignal(state); }, eEventType::rise);
   connect(this, SIGNAL(nIRQSignal(const bool)), this, SLOT(receiver_nIRQ(const bool)), Qt::ConnectionType::QueuedConnection);

   //ui->edit_multple_comand_rec->setText("0000 898A A7D0 C847 C69B C42A C200 C080 CE84 CE87 C081");

}

ReceiverControlPanel::~ReceiverControlPanel()
{
   delete ui;
}

void ReceiverControlPanel::receiverSendComand(const std::vector<bool> & cmd)
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
