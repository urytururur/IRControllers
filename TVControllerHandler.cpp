#include "TVControllerHandler.h"
#include <Arduino.h>

TVControllerHandler::TVControllerHandler(IRsend& irsend)
  :
    tvController{irsend},
    tvStateHandler{tvController}
{}

void TVControllerHandler::sendSignalBasedOnCommandId(uint8_t commandId)
{
  switch(commandId)
  {
    case 1:
      tvController.sendPowerButtonSignal();
      break;
    case 2:
      tvController.sendMuteButtonSignal();
      break;
    case 3:
      sendAndRepeatIRSignal(
        [&controller = this->tvController]() { controller.sendVolumeUpButtonSignal(); },
        2,
        100
      );
      break;
    case 4:
      sendAndRepeatIRSignal(
        [&controller = this->tvController]() { controller.sendVolumeDownButtonSignal(); },
        2,
        100
      );
      break;
    case 5:
      tvController.sendArrowUpButtonSignal();
      break;
    case 6:
      tvController.sendArrowDownButtonSignal();
      break;
    case 7:
      tvController.sendArrowLeftButtonSignal();
      break;
    case 8:
      tvController.sendArrowRightButtonSignal();
      break;
    case 9:
      tvController.sendOKButtonSignal();
      break;
    case 10:
      tvController.sendSourceButtonSignal();
      break;
    case 11:
      tvController.sendHomeButtonSignal();
      break;
    case 12:
      tvController.sendBackButtonSignal();
      break;
    case 13:
      tvController.sendExitButtonSignal();
      break;
    case 14:
      tvController.sendNetflixButtonSignal();
      break;
    case 15:
      tvStateHandler.resetState();
      break;
    case 16:
      tvStateHandler.setLoopArrowUp();
      break;
    case 17:
      tvStateHandler.setLoopArrowDown();
      break;
    case 18:
      tvStateHandler.setLoopArrowLeft();
      break;
    case 19:
      tvStateHandler.setLoopArrowRight();
      break;
    case 20:
      tvStateHandler.setLoopVolumeUp();
      break;
    case 21:
      tvStateHandler.setLoopVolumeDown();
      break;
    case 22:
      sendAndRepeatIRSignal(
        [&controller = this->tvController]() { controller.sendVolumeUpButtonSignal(); },
        6,
        100
      );
      break;
    case 23:
      sendAndRepeatIRSignal(
        [&controller = this->tvController]() { controller.sendVolumeDownButtonSignal(); },
        6,
        100
      );
      break;
      
    default:
      Serial.println("Event registered on 'TV' but no action defined for the incoming callback method argument.");
  }
}

void TVControllerHandler::handleState()
{
  tvStateHandler.handleState();
}

void TVControllerHandler::sendAndRepeatIRSignal(const std::function<void()>& callback, int numberOfTimes, int delayBetweenSignalsMillis)
{
  for(int i{0}; i < numberOfTimes; ++i)
  {
    callback();
    delay(delayBetweenSignalsMillis);
  }
}