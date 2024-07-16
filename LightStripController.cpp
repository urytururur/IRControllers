#include "LightStripController.h"

enum LightStripCodes
{
  LightStripCodes_ON = 0xF7C03F,
  LightStripCodes_OFF = 0xF740BF,
  LightStripCodes_BRIGHTNESS_UP = 0xF700FF,
  LightStripCodes_BRIGHTNESS_DOWN = 0xF7807F,
  LightStripCodes_RED0 = 0xF720DF,
  LightStripCodes_GREEN0 = 0xF7A05F,
  LightStripCodes_BLUE0 = 0xF7609F,
  LightStripCodes_RED1 = 0xF710EF,
  LightStripCodes_GREEN1 = 0xF7906F,
  LightStripCodes_BLUE1 = 0xF750AF,
  LightStripCodes_RED2 = 0xF730CF,
  LightStripCodes_GREEN2 = 0xF7B04F,
  LightStripCodes_BLUE2 = 0xF7708F,
  LightStripCodes_WHITE = 0xF7E01F,
  LightStripCodes_FLASH = 0xF7D02F,
  LightStripCodes_STROBE = 0xF7F00F,
  LightStripCodes_FADE = 0xF7C837,
  LightStripCodes_SMOOTH = 0xF7E817
};

LightStripController::LightStripController(IRsend& irsend)
  : irsend{irsend}
{}

void LightStripController::sendOnButtonSignal()
{
  irsend.sendNEC(LightStripCodes_ON);
}
void LightStripController::sendOffButtonSignal()
{
  irsend.sendNEC(LightStripCodes_OFF);
}
void LightStripController::sendBrightnessUpButtonSignal()
{
  irsend.sendNEC(LightStripCodes_BRIGHTNESS_UP);
}
void LightStripController::sendBrightnessDownButtonSignal()
{
  irsend.sendNEC(LightStripCodes_BRIGHTNESS_DOWN);
}
void LightStripController::sendRed0ButtonSignal()
{
  irsend.sendNEC(LightStripCodes_RED0);
}
void LightStripController::sendGreen0ButtonSignal()
{
  irsend.sendNEC(LightStripCodes_GREEN0);
}
void LightStripController::sendBlue0ButtonSignal()
{
  irsend.sendNEC(LightStripCodes_BLUE0);
}
void LightStripController::sendWhiteButtonSignal()
{
  irsend.sendNEC(LightStripCodes_WHITE);
}
void LightStripController::sendFlashButtonSignal()
{
  irsend.sendNEC(LightStripCodes_FLASH);
}
void LightStripController::sendStrobeButtonSignal()
{
  irsend.sendNEC(LightStripCodes_STROBE);
}
void LightStripController::sendFadeButtonSignal()
{
  irsend.sendNEC(LightStripCodes_FADE);
}
void LightStripController::sendSmoothButtonSignal()
{
  irsend.sendNEC(LightStripCodes_SMOOTH);
}
void LightStripController::sendRed1ButtonSignal()
{
  irsend.sendNEC(LightStripCodes_RED1);
}
void LightStripController::sendGreen1ButtonSignal()
{
  irsend.sendNEC(LightStripCodes_GREEN1);
}
void LightStripController::sendBlue1ButtonSignal()
{
  irsend.sendNEC(LightStripCodes_BLUE1);
}
void LightStripController::sendRed2ButtonSignal()
{
  irsend.sendNEC(LightStripCodes_RED2);
}
void LightStripController::sendGreen2ButtonSignal()
{
  irsend.sendNEC(LightStripCodes_GREEN2);
}
void LightStripController::sendBlue2Buttonsignal()
{
  irsend.sendNEC(LightStripCodes_BLUE2);
}