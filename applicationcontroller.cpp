#include "applicationcontroller.h"

ApplicationController::ApplicationController(QObject *parent)
   : QObject(parent)
   , mPinout()
   , mEvents(mPinout)
   , mReceiverPanel(mPinout, mEvents)
   , mTransmitterPanel(mPinout, mEvents)
{
   mReceiverPanel.setWindowTitle("Receiver control panel");
   mReceiverPanel.show();
   mTransmitterPanel.setWindowTitle("Transmitter control panel");
   mTransmitterPanel.show();
}
