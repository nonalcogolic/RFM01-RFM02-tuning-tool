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
   sEventHandler handler{type, mPinout.getPinState(pin), stateChangedEvent};
   std::lock_guard<std::mutex> lk(mx);
   mEvents.insert({ pin, handler });
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
         auto actualPinState = mPinout.getPinState(pin.first);
         if (actualPinState != pin.second.prevState)
         {
            pin.second.prevState = actualPinState;
            bool rise = false;
            switch (pin.second.type)
            {
            case eEventType::every:
               rise = true;
               break;

            case eEventType::low:
               if (!actualPinState) { rise = true; }
               break;

            case eEventType::high:
               if (actualPinState) { rise = true; }
               break;

            default:
               break;
            }

            if (rise) pin.second.stateChangedFunction(actualPinState);
         }
      }

   }
}
