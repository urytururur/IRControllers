#include "LightStripControllerHandler.h"
#include <Arduino.h>

LightStripControllerHandler::LightStripControllerHandler(IRsend& irsend)
  : lightStripController{irsend} {}

void LightStripControllerHandler::sendSignalBasedOnCommandId(uint8_t commandId)
{
  switch(commandId)
  {
    case 1:
      lightStripController.sendOnButtonSignal();
      break;
    case 2:
      lightStripController.sendOffButtonSignal();
      break;
    case 3:
      lightStripController.sendBrightnessUpButtonSignal();
      break;
    case 4:
      lightStripController.sendBrightnessDownButtonSignal();
      break;
    case 5:
      lightStripController.sendRed0ButtonSignal();
      break;
    case 6:
      lightStripController.sendGreen0ButtonSignal();
      break;
    case 7:
      lightStripController.sendBlue0ButtonSignal();
      break;
    case 8:
      lightStripController.sendWhiteButtonSignal();
      break;
    case 9:
      lightStripController.sendFlashButtonSignal();
      break;
    case 10:
      lightStripController.sendStrobeButtonSignal();
      break;
    case 11:
      lightStripController.sendFadeButtonSignal();
      break;
    case 12:
      lightStripController.sendSmoothButtonSignal();
      break;
    case 13:
      lightStripController.sendRed1ButtonSignal();
      break;
    case 14:
      lightStripController.sendGreen1ButtonSignal();
      break;
    case 15:
      lightStripController.sendBlue1ButtonSignal();
      break;
    case 16:
      lightStripController.sendRed2ButtonSignal();
      break;
    case 17:
      lightStripController.sendGreen2ButtonSignal();
      break;
    case 18:
      lightStripController.sendBlue2Buttonsignal();
      break;
      
    default:
      Serial.println("Event registered on 'TV lights' but no action defined for the incoming callback method argument.");
  }
}