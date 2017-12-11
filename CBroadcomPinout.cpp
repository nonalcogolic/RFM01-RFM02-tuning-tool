#include "CBroadcomPinout.h"

#include <exception>
#include <string>

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
        throw OpenBCMException() ;

    bcm2835_gpio_fsel(static_cast<uint8_t>(ePin::nSel), BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(static_cast<uint8_t>(ePin::SDI), BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(static_cast<uint8_t>(ePin::SCK), BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(static_cast<uint8_t>(ePin::nIRQ), BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(static_cast<uint8_t>(ePin::SDO), BCM2835_GPIO_FSEL_INPT);
}

 CBroadcomPinout::~CBroadcomPinout()
 {
    bcm2835_close();
 }

void CBroadcomPinout::setPinState(const bool state, const ePin pin)
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
