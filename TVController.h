#pragma once
#include "../IRremoteESP8266/src/IRsend.h"

class TVController
{
private:
  IRsend& irsend;

public:
  TVController(IRsend& irsend);

  void sendPowerButtonSignal();
  void sendMuteButtonSignal();
  void sendVolumeUpButtonSignal();
  void sendVolumeDownButtonSignal();
  void sendArrowUpButtonSignal();
  void sendArrowDownButtonSignal();
  void sendArrowLeftButtonSignal();
  void sendArrowRightButtonSignal();
  void sendOKButtonSignal();
  void sendSourceButtonSignal();
  void sendHomeButtonSignal();
  void sendBackButtonSignal();
  void sendExitButtonSignal();
  void sendNetflixButtonSignal();
};