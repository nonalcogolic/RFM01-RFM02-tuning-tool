#include "applicationcontroller.h"

ApplicationController::ApplicationController(QObject *parent)
   : QObject(parent)
   , mReceiverPanel()
   , mTransmitterPanel()
{
   //transmitter
   connect(&mTransmitterPanel, SIGNAL(sendCommand(const std::vector<bool> &)), &mReceiverPanel, SLOT(transmiiterSendCommand(const std::vector<bool> &))); //, Qt::ConnectionType::QueuedConnection
   connect(&mTransmitterPanel, SIGNAL(readStatus(const std::vector<bool> &)), &mReceiverPanel, SLOT(readTrStatus(const std::vector<bool> &))); //, Qt::ConnectionType::QueuedConnection
   connect(&mTransmitterPanel, SIGNAL(startDataTransmittion(const bool, const std::vector<bool> &)), &mReceiverPanel, SLOT(sendData(const bool, const std::vector<bool> &))); //, Qt::ConnectionType::QueuedConnection
   connect(&mReceiverPanel, SIGNAL(dataTransmitionFinished(const bool)), &mTransmitterPanel, SLOT(dataTransmitionFinished(const bool)), Qt::ConnectionType::QueuedConnection);
   connect(&mReceiverPanel, SIGNAL(transmitterStatusChanged(const QString & )), &mTransmitterPanel, SLOT(statusReceived(const QString & )));

   mReceiverPanel.show();
   mTransmitterPanel.show();
}
