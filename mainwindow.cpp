#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <list>

#include <qmessagebox.h>

namespace
{

   std::vector<bool> fromInt(int command, int size)
   {
      std::list<bool> retValue;

      for (int i = 0 ; i < size * 4; ++i)
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
   , mReceiver(mPinout)
   , mTransmitterHandler(mPinout)
   , mEvents(mPinout)
{
   mEvents.listenPin(ePin::nIRQ, [this](const bool state) { emit nIRQSignal(state); }, CGPIOEvent::eEventType::every);
 //  mEvents.listenPin(ePin::nIRQ, [this](const bool state) { emit nIRQSignal(state); }, CGPIOEvent::eEventType::every);

   ui->setupUi(this);
   connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendComand()) );
   connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(readStatus()) );
   connect(ui->but_readTrStatus, SIGNAL(clicked()), this, SLOT(readTrStatus()) );

   connect(ui->but_tr_sendAll, SIGNAL(clicked()), this, SLOT(sendAllTr()) );
   connect(ui->but_rec_Send_all, SIGNAL(clicked()), this, SLOT(sendAllRec()) );

   connect(this, SIGNAL(nIRQSignal(const bool)), this, SLOT(nIRQ(const bool)), Qt::ConnectionType::QueuedConnection);
   connect(ui->transmitter_but, SIGNAL(clicked()), this, SLOT(transmiiterSendComand()));
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
   QMessageBox msg;
   msg.setText(QString("Pin event state :") + ((state)? "high" : "low"));
   msg.exec();

   static int value= 0;
   value = (++value)%100;
   ui->progressBar->setValue(value);
}


void MainWindow::transmiiterSendComand()
{
   const auto size = ui->transmitterCmd->text().size();
   auto comand = ui->transmitterCmd->text().toInt(nullptr, 16);
   const auto bitset = fromInt(comand, size);
   auto data = 0xAAAAAA2DD4AAAAAA;
   const auto bitsetDATA = fromInt(data, 16);

   if (comand == 0xC6)
   {
      mTransmitterHandler.sendData(bitset, bitsetDATA);
   }
   else
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
   auto commandsList = ui->edit_rec->toPlainText().split(R"([,\s]+)");

   for (const auto & comand : commandsList)
   {
      mReceiver.sendComand(fromInt(comand.toInt(nullptr, 16), comand.size()));
      const auto delay = std::chrono::nanoseconds(100);
      std::this_thread::sleep_for(delay);
   }

   readStatus();
}

void MainWindow::sendAllTr()
{

}
