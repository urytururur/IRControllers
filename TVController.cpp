#include "TVController.h"

enum TVCodes
{
  TVCodes_POWER = 0xD5F2A,
  TVCodes_MUTE = 0xC0F3F,
  TVCodes_VOLUME_UP = 0xD0F2F,
  TVCodes_VOLUME_DOWN = 0xD1F2E,
  TVCodes_ARROW_UP = 0xA6F59,
  TVCodes_ARROW_DOWN = 0xA7F58,
  TVCodes_ARROW_LEFT = 0xA9F56,
  TVCodes_ARROW_RIGHT = 0xA8F57,
  TVCodes_OK = 0xBFF4,
  TVCodes_SOURCE = 0x5CFA3,
  TVCodes_HOME = 0xF7F08,
  TVCodes_BACK = 0xD8F27,
  TVCodes_EXIT = 0xF9F06,
  TVCodes_NETFLIX = 0x10FEF
};

TVController::TVController(IRsend& irsend) :
  irsend{irsend}
{}

void TVController::sendPowerButtonSignal()
{
  irsend.sendNikai(TVCodes_POWER);
}
void TVController::sendMuteButtonSignal()
{
  irsend.sendNikai(TVCodes_MUTE);
}
void TVController::sendVolumeUpButtonSignal()
{
  irsend.sendNikai(TVCodes_VOLUME_UP);
}
void TVController::sendVolumeDownButtonSignal()
{
  irsend.sendNikai(TVCodes_VOLUME_DOWN);
}
void TVController::sendArrowUpButtonSignal()
{
  irsend.sendNikai(TVCodes_ARROW_UP);
}
void TVController::sendArrowDownButtonSignal()
{
  irsend.sendNikai(TVCodes_ARROW_DOWN);
}
void TVController::sendArrowLeftButtonSignal()
{
  irsend.sendNikai(TVCodes_ARROW_LEFT);
}
void TVController::sendArrowRightButtonSignal()
{
  irsend.sendNikai(TVCodes_ARROW_RIGHT);
}
void TVController::sendOKButtonSignal()
{
  irsend.sendNikai(TVCodes_OK);
}
void TVController::sendSourceButtonSignal()
{
  irsend.sendNikai(TVCodes_SOURCE);
}
void TVController::sendHomeButtonSignal()
{
  irsend.sendNikai(TVCodes_HOME);
}
void TVController::sendBackButtonSignal()
{
  irsend.sendNikai(TVCodes_BACK);
}
void TVController::sendExitButtonSignal()
{
  irsend.sendNikai(TVCodes_EXIT);
}
void TVController::sendNetflixButtonSignal()
{
  irsend.sendNikai(TVCodes_NETFLIX);
}