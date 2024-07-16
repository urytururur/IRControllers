#pragma once
#include "TVController.h"
#include "TVStateHandler.h"
#include <functional>

class TVControllerHandler
{
private:
  TVController tvController;
  TVStateHandler tvStateHandler;

public:
  TVControllerHandler(IRsend& irsend);

  void sendSignalBasedOnCommandId(uint8_t commandId);
  void handleState();

private:
  void sendAndRepeatIRSignal(const std::function<void()>& callback, int numberOfTimes, int delayBetweenSignalsMillis);
};