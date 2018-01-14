#include "CBroadcomPinout.h"

#include "constants.h"

#include <exception>
#include <string>
#include <chrono>
#include <thread>

#include <bcm2835.h>

void setPinDelay()
{
   std::this_thread::sleep_for(std::chrono::nanoseconds(Constants::CHANGE_LEVEL_DURATION));
}

class OpenBCMException : public std::exception
{
    const std::string mMsg;
public:
    OpenBCMException()
        : mMsg("BCM exception")
    { }

    const char * what() const noexcept override
    {
        return mMsg.c_str();
    }
};



CBroadcomPinout::CBroadcomPinout()
{
   if (!bcm2835_init())
        throw OpenBCMException();
}

CBroadcomPinout::~CBroadcomPinout()
{
   bcm2835_close();
}

void CBroadcomPinout::setPinState(const bool state, const ePin pin)
{
   bcm2835_gpio_write(static_cast<uint8_t>(pin), static_cast<uint8_t>(state));
   setPinDelay();
}

void CBroadcomPinout::setPinStateForce(const bool state, const ePin pin)
{
   bcm2835_gpio_write(static_cast<uint8_t>(pin), static_cast<uint8_t>(state));
}


bool CBroadcomPinout::getPinState(const ePin pin)
{
    return (bcm2835_gpio_lev(static_cast<uint8_t>(pin)) != 0);
}

void CBroadcomPinout::setPinDirrection(const bool isPinOut, const ePin pin)
{
   auto dirrection = (isPinOut) ? BCM2835_GPIO_FSEL_OUTP : BCM2835_GPIO_FSEL_INPT;
   bcm2835_gpio_fsel(static_cast<uint8_t>(pin), dirrection);
}

void CBroadcomPinout::subscribeOn(const ePin pin, const eEventType type)
{
   bcm2835_gpio_clr_afen(static_cast<uint8_t>(pin));
   bcm2835_gpio_clr_aren(static_cast<uint8_t>(pin));
   bcm2835_gpio_clr_fen(static_cast<uint8_t>(pin));
   bcm2835_gpio_clr_ren(static_cast<uint8_t>(pin));
   bcm2835_gpio_clr_hen(static_cast<uint8_t>(pin));
   bcm2835_gpio_clr_len(static_cast<uint8_t>(pin));


   switch (type) {
   case eEventType::fall:
      bcm2835_gpio_pud(BCM2835_GPIO_PUD_UP);
      bcm2835_gpio_pudclk(static_cast<uint8_t>(pin),true);
      bcm2835_gpio_fen(static_cast<uint8_t>(pin));

      break;

   case eEventType::rise:
      bcm2835_gpio_ren(static_cast<uint8_t>(pin));
      break;

   case eEventType::high:
      bcm2835_gpio_hen(static_cast<uint8_t>(pin));
      break;

   case eEventType::low:
      bcm2835_gpio_len(static_cast<uint8_t>(pin));
      break;

   default:
      break;
   }
}

void CBroadcomPinout::unsubscribeFrom(const ePin pin, const eEventType type)
{
   bcm2835_gpio_clr_afen(static_cast<uint8_t>(pin));
   bcm2835_gpio_clr_aren(static_cast<uint8_t>(pin));
   bcm2835_gpio_clr_fen(static_cast<uint8_t>(pin));
   bcm2835_gpio_clr_ren(static_cast<uint8_t>(pin));
   bcm2835_gpio_clr_hen(static_cast<uint8_t>(pin));
   bcm2835_gpio_clr_len(static_cast<uint8_t>(pin));
}

bool CBroadcomPinout::checkEvent(const ePin pin)
{
   return bcm2835_gpio_eds(static_cast<int8_t>(pin)) != 0;
}

void CBroadcomPinout::resetEvent(const ePin pin)
{
   bcm2835_gpio_set_eds(static_cast<int8_t>(pin));
}
