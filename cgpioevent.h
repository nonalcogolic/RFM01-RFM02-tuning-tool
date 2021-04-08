#ifndef CGPIOEVENT_H
#define CGPIOEVENT_H


#include "ipinout.h"
#include "helper.h"

#include <functional>
#include <map>
#include <thread>
#include <memory>
#include <mutex>


class CGPIOEvent
{
public:
   CGPIOEvent(IPinOut & pinout);
   ~CGPIOEvent();

   void listenPin(const ePin pin, std::function<void(bool)> stateChangedEvent, const eEventType type);
   void removeEvent(const ePin pin, const eEventType type);

   void startThread();

private:
   IPinOut & mPinout;
   std::map<ePin, std::function<void(bool)>> mEvents;

private: //thread communications
   void eventLoop();
   bool mTerminateThread;
   std::unique_ptr<std::thread> mEventThread;
   std::mutex mx;

};

#endif // CGPIOEVENT_H
