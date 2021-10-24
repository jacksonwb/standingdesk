#include "BumpStepper.h"

BumpStepper::BumpStepper(uint8_t interface, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, bool enable) : AccelStepper::AccelStepper(interface, pin1, pin2, pin3, pin4, enable) {
  
}

// TODO: Fix this method. The idea is to bump, as a way to provide haptic feedback.
void BumpStepper::bump() {
    _direction = DIRECTION_CW;
    for (int i=0; i<10; i++) {
      step(1);
      delay(10);
    }
    _direction = DIRECTION_CCW;
    for (int i=0; i<10; i++) {
      step(1);
      delay(10);

    }
     _direction = DIRECTION_CW;
    for (int i=0; i<10; i++) {
      step(1);
      delay(10);
    }
}
