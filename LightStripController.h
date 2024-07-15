#pragma once
#include "IIRController.h"
#include "../IRremoteESP8266/src/IRsend.h"

class LightStripController : public IIRController
{
private:
  IRsend& irsend;

public:
  LightStripController(IRsend& irsend);

  void sendSignalBasedOnCommandId(uint8_t value);
  void sendAndRepeatIRSignal(int code, int numberOfTimes, int delayBetweenSignalsMillis);
};