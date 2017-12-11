#ifndef CGPIOEVENT_H
#define CGPIOEVENT_H


#include "ipinout.h"

#include <functional>
#include <map>
#include <thread>
#include <memory>
#include <mutex>


class CGPIOEvent
{
public:
   enum class eEventType
   {
      low,
      high,
      every
   };

   CGPIOEvent(IPinOut & pinout);
   ~CGPIOEvent();

   void listenPin(const ePin pin, std::function<void(bool)> stateChangedEvent, const eEventType type);
   void removeEvent(const ePin pin);

private:
   struct sEventHandler
   {
      eEventType type;
      bool prevState;
      std::function<void(bool)> stateChangedFunction;
   };

   IPinOut & mPinout;
   std::map<ePin, sEventHandler> mEvents;

private: //thread communications
   void eventLoop();
   bool mTerminateThread;
   std::unique_ptr<std::thread> mEventThread;
   std::mutex mx;

};

#endif // CGPIOEVENT_H
