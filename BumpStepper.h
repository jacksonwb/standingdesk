#include <AccelStepper.h>

class BumpStepper: public AccelStepper
{
    public:
        BumpStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5, bool enable = true);
        void bump();
};
