#pragma once
#include "LightStripController.h"
#include <functional>

class LightStripControllerHandler
{
private:
  LightStripController lightStripController;

public:
  LightStripControllerHandler(IRsend& irsend);

  void sendSignalBasedOnCommandId(uint8_t commandId);
};