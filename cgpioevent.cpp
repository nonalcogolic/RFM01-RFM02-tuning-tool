#include "cgpioevent.h"

#include "qdebug.h"

CGPIOEvent::CGPIOEvent(IPinOut & pinout)
   : mPinout(pinout)
   , mTerminateThread(false)
   , mEventThread(nullptr)
{
   mEventThread = std::unique_ptr<std::thread>(new std::thread{ &CGPIOEvent::eventLoop, this });
}

CGPIOEvent::~CGPIOEvent()
{
   mTerminateThread = true;
   mEventThread->join();
}

void CGPIOEvent::listenPin(const ePin pin, std::function<void(bool)> stateChangedEvent, const eEventType type)
{
   mPinout.setPinDirrection(false, pin);
   mPinout.subscribeOn(pin, type);
   std::lock_guard<std::mutex> lk(mx);
   mEvents.emplace(pin, stateChangedEvent);
   qDebug() << "CGPIOEvent::listenPin() inserted pin";
}


void CGPIOEvent::removeEvent(const ePin pin)
{
   std::lock_guard<std::mutex> lk(mx);
   mEvents.erase(pin);
}


void CGPIOEvent::eventLoop()
{
   while (!mTerminateThread)
   {
      std::lock_guard<std::mutex> lk(mx);
      for (auto & pin : mEvents)
      {
         if (mPinout.checkEvent(pin.first))
         {
            mPinout.resetEvent(pin.first);
            pin.second(true);
         }
      }

   }
}
