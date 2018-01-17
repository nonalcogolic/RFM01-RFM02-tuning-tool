#include "applicationcontroller.h"

ApplicationController::ApplicationController(QObject *parent)
   : QObject(parent)
   , mPinout()
   , mEvents(mPinout)
   , mReceiverPanel(mPinout, mEvents)
   , mTransmitterPanel(mPinout, mEvents)
{
   mReceiverPanel.show();
   mTransmitterPanel.show();
}
