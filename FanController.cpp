#include "FanController.h"
#include <Arduino.h>

enum FanCodes
{
  FanCodes_POWER = 0xCF3E916,
  FanCodes_MODE  = 0xCF3E11E,
  FanCodes_SPEED = 0xCF3619E,
  FanCodes_TIMER = 0xCF339C6,
  FanCodes_ROTATE = 0xCF3A956
};

FanController::FanController(IRsend& irsend)
  : irsend{irsend}
{}

void FanController::sendSignalBasedOnCommandId(uint8_t value)
{
  switch(value)
  {
    //Fan remote commands
    case 1:
      irsend.sendNEC(FanCodes_POWER);
      Serial.println("Emitted IR signal based on the value of 'FanCodes_POWER'.");
      break;
    case 2:
      irsend.sendNEC(FanCodes_MODE);
      Serial.println("Emitted IR signal based on the value of 'FanCodes_MODE'.");
      break;
    case 3:
      irsend.sendNEC(FanCodes_SPEED);
      Serial.println("Emitted IR signal based on the value of 'FanCodes_SPEED'.");
      break;
    case 4:
      irsend.sendNEC(FanCodes_TIMER);
      Serial.println("Emitted IR signal based on the value of 'FanCodes_TIMER'.");
      break;
    case 5:
      irsend.sendNEC(FanCodes_ROTATE);
      Serial.println("Emitted IR signal based on the value of 'FanCodes_ROTATE'.");
      break;
    case 6:
      sendAndRepeatIRSignal(FanCodes_ROTATE, 2, 1000);
      break;
      
    default:
      Serial.println("Event registered on 'Fan' but no action defined for the incoming callback method argument.");
  }
}

void FanController::sendAndRepeatIRSignal(int code, int numberOfTimes, int delayBetweenSignalsMillis)
{
  for(int i{0}; i < numberOfTimes; ++i)
  {
    irsend.sendNEC(code);
    Serial.print("Emitted IR signal from TVController -> Protocol: NEC, Code: ");
    Serial.print(code);
    Serial.println();
    delay(delayBetweenSignalsMillis);
  }
}