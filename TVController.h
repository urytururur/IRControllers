#pragma once
#include "IIRController.h"
#include "../IRremoteESP8266/src/IRsend.h"

class TVController : public IIRController
{
private:
  IRsend& irsend;

  bool loopArrowUp;
  bool loopArrowDown;
  bool loopArrowLeft;
  bool loopArrowRight;
  bool loopVolumeUp;
  bool loopVolumeDown;

  void setLoopArrowUp();
  void setLoopArrowDown();
  void setLoopArrowLeft();
  void setLoopArrowRight();
  void setLoopVolumeUp();
  void setLoopVolumeDown();

public:
  TVController(IRsend& irsend);

  void sendIRSignalsBasedOnState();
  void sendSignalBasedOnCommandId(uint8_t value);
  void sendAndRepeatIRSignal(int code, int numberOfTimes, int delayBetweenSignalsMillis);
  void resetState();
  void printState();

  bool getLoopArrowUp();
  bool getLoopArrowDown();
  bool getLoopArrowLeft();
  bool getLoopArrowRight();
  bool getLoopVolumeUp();
  bool getLoopVolumeDown();
};