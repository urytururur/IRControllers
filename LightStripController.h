#pragma once
#include "../IRremoteESP8266/src/IRsend.h"

class LightStripController
{
private:
  IRsend& irsend;

public:
  LightStripController(IRsend& irsend);

  void sendOnButtonSignal();
  void sendOffButtonSignal();
  void sendBrightnessUpButtonSignal();
  void sendBrightnessDownButtonSignal();
  void sendRed0ButtonSignal();
  void sendGreen0ButtonSignal();
  void sendBlue0ButtonSignal();
  void sendWhiteButtonSignal();
  void sendFlashButtonSignal();
  void sendStrobeButtonSignal();
  void sendFadeButtonSignal();
  void sendSmoothButtonSignal();
  void sendRed1ButtonSignal();
  void sendGreen1ButtonSignal();
  void sendBlue1ButtonSignal();
  void sendRed2ButtonSignal();
  void sendGreen2ButtonSignal();
  void sendBlue2Buttonsignal();
};