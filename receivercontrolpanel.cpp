#include "receivercontrolpanel.h"
#include "ui_receivercontrolpanel.h"

#include <list>
#include <future>

#include <qmessagebox.h>
#include <qdebug.h>

namespace
{

   std::vector<bool> fromInt(int command, int charsInCommand)
   {
      std::list<bool> retValue;

      for (int i = 0 ; i < charsInCommand * 4; ++i)
      {
         bool value = (command >> i) % 2;
         retValue.push_front(value);
      }

      return std::vector<bool>(retValue.cbegin(), retValue.cend());
   }
}


ReceiverControlPanel::ReceiverControlPanel(QWidget *parent)
   : QWidget(parent)
   , ui(new Ui::ReceiverControlPanel)
   , mPinout()
   , mReceiver(mPinout)
   , mTransmitterHandler(mPinout)
   , mEvents(mPinout)
   , trControlPanel()
{
   mEvents.listenPin(ePin::nIRQ, [this](const bool state) { emit nIRQSignal(state); }, eEventType::rise);

   ui->setupUi(this);
   connect(ui->pushButton_read_status, SIGNAL(clicked()), this, SLOT(receiverReadStatus()));

   //transmitter
   connect(&trControlPanel, SIGNAL(sendCommand(const std::vector<bool> &)), this, SLOT(transmiiterSendCommand(const std::vector<bool> &))); //, Qt::ConnectionType::QueuedConnection
   connect(&trControlPanel, SIGNAL(readStatus(const std::vector<bool> &)), this, SLOT(readTrStatus(const std::vector<bool> &))); //, Qt::ConnectionType::QueuedConnection
   connect(&trControlPanel, SIGNAL(startDataTransmittion(const bool, const std::vector<bool> &)), this, SLOT(sendData(const bool, const std::vector<bool> &))); //, Qt::ConnectionType::QueuedConnection
   connect(this, SIGNAL(dataTransmitionFinished(const bool)), &trControlPanel, SLOT(dataTransmitionFinished(const bool)), Qt::ConnectionType::QueuedConnection);
   connect(this, SIGNAL(transmitterStatusChanged(const QString & )), &trControlPanel, SLOT(statusReceived(const QString & )));

   connect(this, SIGNAL(nIRQSignal(const bool)), this, SLOT(nIRQ(const bool)), Qt::ConnectionType::QueuedConnection);

   //ui->edit_multple_comand_rec->setText("0000 898A A7D0 C847 C69B C42A C200 C080 CE84 CE87 C081");

   trControlPanel.show();
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

void ReceiverControlPanel::nIRQ(const bool state)
{
   static int value= 0;
   value = (++value)%100;
   ui->progressBar->setValue(value);
}


void ReceiverControlPanel::transmiiterSendCommand(const std::vector<bool> & cmd)
{
   mTransmitterHandler.sendComand(cmd);
}

void ReceiverControlPanel::readTrStatus(const std::vector<bool> & readstatusCMD)
{
   auto word = mTransmitterHandler.readStatus(readstatusCMD);
   QString result;
   for (auto symb : word)
   {
      result += (symb) ? "1" : "0";
   }

   emit transmitterStatusChanged(result);
}

void ReceiverControlPanel::sendData(const bool throughFSK, const std::vector<bool> transmitDataSDIcmd)
{
   qDebug() << "ReceiverControlPanel::sendData";
   if (throughFSK)
   {
      std::async(std::launch::async, &ReceiverControlPanel::sendDataFSK, this);
   }
   else
   {
      std::async(std::launch::async, &ReceiverControlPanel::sendDataSDI, this, transmitDataSDIcmd);
   }
}

void ReceiverControlPanel::sendDataFSK()
{
   transmitionIsOver = false;
   connect(this, SIGNAL(nIRQTransmitterSignal(const bool)), this, SLOT(nIRQTransmitterFSK(const bool)), Qt::ConnectionType::QueuedConnection);
   mEvents.listenPin(ePin::tr_NIRQ, [this](const bool state) { emit nIRQTransmitterSignal(state); }, eEventType::fall);
   mTransmitterHandler.sendDataFSK();
}

void ReceiverControlPanel::nIRQTransmitterFSK(const bool state)
{
   std::ignore = state; static int count = 0; qDebug() << "nIRQTransmitterFSK " << ++count;
   if (!mTransmitterHandler.bitSyncArived())
   {
      count = 0;
      transmitionIsOver = true;
      disconnect(this, SIGNAL(nIRQTransmitterSignal(const bool)), this, SLOT(nIRQTransmitterFSK(const bool)));
      mEvents.removeEvent(ePin::tr_NIRQ, eEventType::fall);
      mTransmitterHandler.stopSendDataFSK();
      emit dataTransmitionFinished(true);
   }
}


void ReceiverControlPanel::sendDataSDI(const std::vector<bool> transmitDataSDIcmd)
{
   transmitionIsOver = false;
   connect(this, SIGNAL(nIRQTransmitterSignal(const bool)), this, SLOT(nIRQTransmitterSDI(const bool)), Qt::ConnectionType::QueuedConnection);
   mEvents.listenPin(ePin::tr_NIRQ, [this](const bool state) { emit nIRQTransmitterSignal(state); }, eEventType::fall);
   mTransmitterHandler.sendDataSDI(transmitDataSDIcmd);
}

void ReceiverControlPanel::nIRQTransmitterSDI(const bool state)
{
   std::ignore = state; static int count = 0; qDebug() << "nIRQTransmitterSDI " << ++count;
   if (!mTransmitterHandler.bitSyncArived())
   {
      count = 0;
      transmitionIsOver = true;
      mTransmitterHandler.stopSendDataSDI();
      mEvents.removeEvent(ePin::tr_NIRQ, eEventType::fall);
      emit dataTransmitionFinished(false);
      disconnect(this, SIGNAL(nIRQTransmitterSignal(const bool)), this, SLOT(nIRQTransmitterSDI(const bool)));
      qDebug() << "disconnected";
   }
}
