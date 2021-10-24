#include "BumpStepper.h"
#include <Bounce2.h>
#include <limits.h>

#define BUTTON1 8
#define BUTTON2 9
#define BUTTON3 10
#define BUTTON4 11
#define B_INTERVAL 10
#define CONST_SPEED 9

//#define MAX_SPEED 7 //slow mode - 2.37 A Peak
#define MAX_SPEED 11 //fast mode - 3.31 A Peak

#define driverENA 5
#define driverDIR 6
#define driverPUL 7
#define STEP_FACTOR 200
#define ACCEL_FACTOR 7

long low_pos = 0;
long high_pos = 0;

using namespace Bounce2;
   
BumpStepper stepper = BumpStepper(AccelStepper::DRIVER, driverPUL, driverDIR);
Button up_button = Button();
Button down_button = Button();
Button low_button = Button();
Button high_button = Button();

bool up_button_state = false;
bool down_button_state = false;
bool high_button_state = false;
bool low_button_state = false;

void setup() {
  // Setup buttons
  up_button.attach(BUTTON4, INPUT_PULLUP);
  up_button.setPressedState(LOW);
  up_button.interval(B_INTERVAL);

  down_button.attach(BUTTON3, INPUT_PULLUP);
  down_button.setPressedState(LOW);
  down_button.interval(B_INTERVAL);

  high_button.attach(BUTTON2, INPUT_PULLUP);
  high_button.setPressedState(LOW);
  high_button.interval(B_INTERVAL);

  low_button.attach(BUTTON1, INPUT_PULLUP);
  low_button.setPressedState(LOW);
  low_button.interval(B_INTERVAL);


  // Setup stepper
  stepper.setEnablePin(driverENA);
  stepper.setPinsInverted(true, false, false);
  stepper.setMaxSpeed(MAX_SPEED * STEP_FACTOR);
  stepper.setAcceleration(ACCEL_FACTOR * STEP_FACTOR);
}

void bump() {
  stepper.move(1);
  stepper.runSpeedToPosition();
}

void loop() {
  up_button.update();
  down_button.update();
  high_button.update();
  low_button.update();
  stepper.run();

  if (up_button.pressed()) {
    stepper.enableOutputs();
    stepper.moveTo(100000000);
  }
  else if (up_button.released()) {
    stepper.stop();
  }

  if(down_button.pressed()) {
    stepper.enableOutputs();
    stepper.moveTo(-1000000000);
  }
  else if (down_button.released()) {
    stepper.stop();
  }

  if (high_button.released()) {
    if (high_button.previousDuration() > 1000) {
      high_pos = stepper.currentPosition();
    } else {
      stepper.enableOutputs();
      stepper.moveTo(high_pos);
    }
  }

  if (low_button.released()) {
    if (low_button.previousDuration() > 1000) {
      low_pos = stepper.currentPosition();
    } else {
      stepper.enableOutputs();
      stepper.moveTo(low_pos + 10);
    }
  }

  if (!stepper.isRunning()) {
    stepper.disableOutputs();
  }
}
