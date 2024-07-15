#pragma once
#include "IIRController.h"
#include "../IRremoteESP8266/src/IRsend.h"

class FanController : public IIRController
{
private:
  IRsend& irsend;

public:
  FanController(IRsend& irsend);

  void sendSignalBasedOnUpdateValue(uint8_t value);
  void sendAndRepeatIRSignal(int code, int numberOfTimes, int delayBetweenSignalsMillis);
};