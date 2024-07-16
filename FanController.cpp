#include "FanController.h"

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

void FanController::sendPowerButtonSignal()
{
  irsend.sendNEC(FanCodes_POWER);
}
void FanController::sendModeButtonSignal()
{
  irsend.sendNEC(FanCodes_MODE);
}
void FanController::sendSpeedButtonSignal()
{
  irsend.sendNEC(FanCodes_SPEED);
}
void FanController::sendTimerButtonSignal()
{
  irsend.sendNEC(FanCodes_TIMER);
}
void FanController::sendRotateButtonSignal()
{
  irsend.sendNEC(FanCodes_ROTATE);
}