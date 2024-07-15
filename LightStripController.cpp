#include "LightStripController.h"
#include <Arduino.h>

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

void LightStripController::sendSignalBasedOnCommandId(uint8_t value)
{
  switch(value)
  {
    //Light strip remote commands
    case 1:
      irsend.sendNEC(LightStripCodes_ON);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_ON'.");
      break;
    case 2:
      irsend.sendNEC(LightStripCodes_OFF);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_OFF'.");
      break;
    case 3:
      irsend.sendNEC(LightStripCodes_BRIGHTNESS_UP);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_BRIGHTNESS_UP'.");
      break;
    case 4:
      irsend.sendNEC(LightStripCodes_BRIGHTNESS_DOWN);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_BRIGHTNESS_DOWN'.");
      break;
    case 5:
      irsend.sendNEC(LightStripCodes_RED0);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_RED0'.");
      break;
    case 6:
      irsend.sendNEC(LightStripCodes_GREEN0);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_GREEN0'.");
      break;
    case 7:
      irsend.sendNEC(LightStripCodes_BLUE0);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_BLUE0'.");
      break;
    case 8:
      irsend.sendNEC(LightStripCodes_WHITE);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_WHITE'.");
      break;
    case 9:
      irsend.sendNEC(LightStripCodes_FLASH);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_FLASH'.");
      break;
    case 10:
      irsend.sendNEC(LightStripCodes_STROBE);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_STROBE'.");
      break;
    case 11:
      irsend.sendNEC(LightStripCodes_FADE);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_FADE'.");
      break;
    case 12:
      irsend.sendNEC(LightStripCodes_SMOOTH);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_SMOOTH'."); 
      break;
    case 13:
      irsend.sendNEC(LightStripCodes_RED1);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_RED1'.");
      break;
    case 14:
      irsend.sendNEC(LightStripCodes_GREEN1);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_GREEN1'.");
      break;
    case 15:
      irsend.sendNEC(LightStripCodes_BLUE1);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_BLUE1'.");
      break;
    case 16:
      irsend.sendNEC(LightStripCodes_RED2);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_RED2'.");
      break;
    case 17:
      irsend.sendNEC(LightStripCodes_GREEN2);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_GREEN2'.");
      break;
    case 18:
      irsend.sendNEC(LightStripCodes_BLUE2);
      Serial.println("Emitted IR signal based on the value of 'LightStripCodes_BLUE2'.");
      break;
      
    default:
      Serial.println("Event registered on 'TV lights' but no action defined for the incoming callback method argument.");
  }
}

void LightStripController::sendAndRepeatIRSignal(int code, int numberOfTimes, int delayBetweenSignalsMillis)
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