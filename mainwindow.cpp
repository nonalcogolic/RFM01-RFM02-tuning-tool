#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "command.h"

#include <list>

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


MainWindow::MainWindow(QWidget *parent)
   : QWidget(parent)
   , ui(new Ui::MainWindow)
   , mPinout()
   , mReceiver(mPinout)
   , mTransmitterHandler(mPinout)
   , mEvents(mPinout)
{
   mEvents.listenPin(ePin::nIRQ, [this](const bool state) { emit nIRQSignal(state); }, eEventType::rise);

   ui->setupUi(this);
   connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendComand()) );
   connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(readStatus()) );
   connect(ui->but_readTrStatus, SIGNAL(clicked()), this, SLOT(readTrStatus()) );

   connect(ui->but_tr_sendAll, SIGNAL(clicked()), this, SLOT(sendAllTr()) );
   connect(ui->but_rec_Send_all, SIGNAL(clicked()), this, SLOT(sendAllRec()) );
   connect(ui->pushButton_DataFSK, SIGNAL(clicked()), this, SLOT(sendDataFSK()) );

   connect(this, SIGNAL(nIRQSignal(const bool)), this, SLOT(nIRQ(const bool)), Qt::ConnectionType::QueuedConnection);
   connect(ui->transmitter_but, SIGNAL(clicked()), this, SLOT(transmiiterSendComand()));

   ui->edit_multple_comand_rec->setText("0000 898A A7D0 C847 C69B C42A C200 C080 CE84 CE87 C081");
   ui->edit_multyple_comand_Tr->setText("CC00 8886 A7D0 C847 D240 C220");
}

MainWindow::~MainWindow()
{
   delete ui;
}


void MainWindow::sendComand()
{
   const auto size = ui->lineEdit->text().size();
   auto comand = ui->lineEdit->text().toInt(nullptr, 16);
   const auto bitset = fromInt(comand, size);
   mReceiver.sendComand(bitset);

   QString result;

   for (auto symb : bitset)
   {
      result += (symb) ? "1" : "0";
   }

   ui->label->setText(result);
}

void MainWindow::readStatus()
{
   auto word = mReceiver.readStatus();

   QString result;

   for (auto symb : word)
   {
      result += (symb) ? "1" : "0";
   }

   ui->lineEdit_2->setText(result);
}

void MainWindow::nIRQ(const bool state)
{
   static int value= 0;
   value = (++value)%100;
   ui->progressBar->setValue(value);
}


void MainWindow::transmiiterSendComand()
{
   const auto size = ui->transmitterCmd->text().size();
   auto comand = ui->transmitterCmd->text().toInt(nullptr, 16);
   const auto bitset = fromInt(comand, size);

   {
      mTransmitterHandler.sendComand(bitset);
   }

   ui->label_2->setText(QString::number(comand, 16));

}


void MainWindow::readTrStatus()
{
   auto word = mTransmitterHandler.readStatus();
   QString result;
   for (auto symb : word)
   {
      result += (symb) ? "1" : "0";
   }
   ui->ed_tr->setText(result);
}

void MainWindow::sendAllRec()
{
   QRegExp rx { R"([,\s]+)" };
   auto commandsList = ui->edit_multple_comand_rec->toPlainText().split(rx);
   for (const auto & comand : commandsList)
   {
      qDebug() << comand ;
      mReceiver.sendComand(fromInt(comand.toInt(nullptr, 16), comand.size()));
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
   }
   readStatus();
}

void MainWindow::sendAllTr()
{
   QRegExp rx { R"([,\s]+)" };
   auto commandsList = ui->edit_multyple_comand_Tr->toPlainText().split(rx);

   for (const auto & comand : commandsList)
   {
      qDebug() << comand ;
      mTransmitterHandler.sendComand(fromInt(comand.toInt(nullptr, 16), comand.size()));
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
   }
}

void MainWindow::sendDataFSK()
{
   transmitionIsOver = false;
   connect(this, SIGNAL(nIRQTransmitterSignal(const bool)), this, SLOT(nIRQTransmitterFSK(const bool)), Qt::ConnectionType::QueuedConnection);
   mEvents.listenPin(ePin::tr_NIRQ, [this](const bool state) { emit nIRQTransmitterSignal(state); }, eEventType::fall);
   mTransmitterHandler.sendComand(CMD::CMD_ENABLE_TX_SYNC());
   mTransmitterHandler.sendComand(CMD::CMD_SWITCH_ON_FSK_MODE());
   mTransmitterHandler.sendDataFSK();
}

void MainWindow::nIRQTransmitterFSK(const bool state)
{
   std::ignore = state;
   static int count = 0;
   qDebug() << "nIRQTransmitterFSK " << ++count;
   if (!mTransmitterHandler.bitSyncArived())
   {
      count = 0;
      transmitionIsOver = true;
      mTransmitterHandler.sendComand(CMD::CMD_SWITCH_OFF());
      mTransmitterHandler.sendComand(CMD::CMD_DISABLE_TX_SYNC());
      disconnect(this, SIGNAL(nIRQTransmitterSignal(const bool)), this, SLOT(nIRQTransmitterFSK(const bool)));
      mEvents.removeEvent(ePin::tr_NIRQ, eEventType::fall);
      readTrStatus();
   }
}

void MainWindow::sendDataSDI()
{
   transmitionIsOver = false;
   connect(this, SIGNAL(nIRQTransmitterSignal(const bool)), this, SLOT(nIRQTransmitterSDI(const bool)), Qt::ConnectionType::QueuedConnection);
   mEvents.listenPin(ePin::tr_NIRQ, [this](const bool state) { emit nIRQTransmitterSignal(state); }, eEventType::fall);
   mTransmitterHandler.sendComand(CMD::CMD_ENABLE_TX_SYNC());
   mTransmitterHandler.sendDataSDI();
}

void MainWindow::nIRQTransmitterSDI(const bool state)
{
   std::ignore = state;
   static int count = 0;
   qDebug() << "nIRQTransmitterSDI " << ++count;
   if (!mTransmitterHandler.bitSyncArived())
   {
      count = 0;
      transmitionIsOver = true;
      mTransmitterHandler.stopSendDataSDI();
      disconnect(this, SIGNAL(nIRQTransmitterSignal(const bool)), this, SLOT(nIRQTransmitterFSK(const bool)));
      mEvents.removeEvent(ePin::tr_NIRQ, eEventType::fall);
      mTransmitterHandler.sendComand(CMD::CMD_DISABLE_TX_SYNC());
      readTrStatus();
   }
}
