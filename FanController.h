#pragma once
#include "../IRremoteESP8266/src/IRsend.h"

class FanController
{
private:
  IRsend& irsend;

public:
  FanController(IRsend& irsend);

  void sendPowerButtonSignal();
  void sendModeButtonSignal();
  void sendSpeedButtonSignal();
  void sendTimerButtonSignal();
  void sendRotateButtonSignal();
};