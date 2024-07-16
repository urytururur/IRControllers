#include "FanControllerHandler.h"
#include <Arduino.h>

FanControllerHandler::FanControllerHandler(IRsend& irsend)
  :
    fanController{irsend}
{}

void FanControllerHandler::sendSignalBasedOnCommandId(uint8_t commandId)
{
  switch(commandId)
  {
    case 1:
      fanController.sendPowerButtonSignal();
      break;
    case 2:
      fanController.sendModeButtonSignal();
      break;
    case 3:
      fanController.sendSpeedButtonSignal();
      break;
    case 4:
      fanController.sendTimerButtonSignal();
      break;
    case 5:
      fanController.sendRotateButtonSignal();
      break;
    case 6:
      sendAndRepeatIRSignal(
        [&controller = this->fanController]() { controller.sendRotateButtonSignal(); },
        2,
        1000
      );
      break;
      
    default:
      Serial.println("Event registered on 'Fan' but no action defined for the incoming callback method argument.");
  }
}

void FanControllerHandler::sendAndRepeatIRSignal(const std::function<void()>& callback, int numberOfTimes, int delayBetweenSignalsMillis)
{
  for(int i{0}; i < numberOfTimes; ++i)
  {
    callback();
    delay(delayBetweenSignalsMillis);
  }
}