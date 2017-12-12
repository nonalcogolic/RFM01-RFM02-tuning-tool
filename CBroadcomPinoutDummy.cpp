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

CBroadcomPinout::CBroadcomPinout()
{}

CBroadcomPinout::~CBroadcomPinout()
{}

void CBroadcomPinout::setPinState(const bool state, const ePin pin)
{}


bool CBroadcomPinout::getPinState(const ePin pin)
{
    return false;
}

void CBroadcomPinout::setPinDirrection(const bool isPinOut, const ePin pin)
{}
