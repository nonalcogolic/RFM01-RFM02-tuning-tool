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
   mEvents[pin] = stateChangedEvent;
   qDebug() << "CGPIOEvent::listenPin() inserted pin";
}


void CGPIOEvent::removeEvent(const ePin pin, const eEventType type)
{
   mPinout.unsubscribeFrom(pin, type);
   std::lock_guard<std::mutex> lk(mx);
   mEvents.erase(pin);
   qDebug() << "CGPIOEvent::removeEvent()";
}


void CGPIOEvent::eventLoop()
{
   while (!mTerminateThread)
   {
      decltype(mEvents) events;
      {
         std::lock_guard<std::mutex> lk(mx);
         events = mEvents;
      }

      for (auto & pin : events)
      {
         if (mPinout.checkEvent(pin.first))
         {
            mPinout.resetEvent(pin.first);
            pin.second(true);
         }
      }
      //std::this_thread::sleep_for(std::chrono::nanoseconds(500));

   }
}
