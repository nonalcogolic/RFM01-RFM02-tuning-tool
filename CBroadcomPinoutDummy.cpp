#include "CBroadcomPinout.h"

#include <exception>
#include <string>

class OpenBCMException : public std::exception
{
    const std::string mMsg;
public:
    OpenBCMException()
        : mMsg("BCM exception")
    {}

    const char * what() const noexcept override
    {
        return mMsg.c_str();
    }
};

#include <qdebug.h>

CBroadcomPinout::CBroadcomPinout()
{
   qDebug() << __FUNCTION__ << "Dummy" ;
}

CBroadcomPinout::~CBroadcomPinout()
{}

void CBroadcomPinout::setPinState(const bool state, const ePin pin)
{}

void CBroadcomPinout::setPinStateForce(const bool state, const ePin pin)
{}

bool CBroadcomPinout::getPinState(const ePin pin)
{
    return false;
}

void CBroadcomPinout::setPinDirrection(const bool isPinOut, const ePin pin)
{}

void CBroadcomPinout::subscribeOn(const ePin pin, const eEventType type)
{}

void CBroadcomPinout::unsubscribeFrom(const ePin pin, const eEventType type)
{}

bool CBroadcomPinout::checkEvent(const ePin pin)
{
   return false;
}

void CBroadcomPinout::resetEvent(const ePin pin)
{}
