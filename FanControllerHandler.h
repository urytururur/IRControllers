#pragma once
#include "FanController.h"
#include <functional>

class FanControllerHandler
{
private:
  FanController fanController;

public:
  FanControllerHandler(IRsend& irsend);

  void sendSignalBasedOnCommandId(uint8_t commandId);

private:
  void sendAndRepeatIRSignal(const std::function<void()>& func, int numberOfTimes, int delayBetweenSignalsMillis);
};