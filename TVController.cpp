#include "TVController.h"
#include <Arduino.h>

enum TVCodes
{
  TVCodes_TOGGLE_ON = 0xD5F2A,
  TVCodes_MUTE = 0xC0F3F,
  TVCodes_VOLUME_UP = 0xD0F2F,
  TVCodes_VOLUME_DOWN = 0xD1F2E,
  TVCodes_ARROW_UP = 0xA6F59,
  TVCodes_ARROW_DOWN = 0xA7F58,
  TVCodes_ARROW_LEFT = 0xA9F56,
  TVCodes_ARROW_RIGHT = 0xA8F57,
  TVCodes_OK = 0xBFF4,
  TVCodes_AV = 0x5CFA3,
  TVCodes_HOME = 0xF7F08,
  TVCodes_BACK = 0xD8F27,
  TVCodes_EXIT = 0xF9F06,
  TVCodes_NETFLIX = 0x10FEF
};

void TVController::setLoopArrowUp()
{
  resetState();
  loopArrowUp = true;
}
void TVController::setLoopArrowDown()
{
  resetState();
  loopArrowDown = true;
}
void TVController::setLoopArrowLeft()
{
  resetState();
  loopArrowLeft = true;
}
void TVController::setLoopArrowRight()
{
  resetState();
  loopArrowRight = true;
}
void TVController::setLoopVolumeUp()
{
  resetState();
  loopVolumeUp = true;
}
void TVController::setLoopVolumeDown()
{
  resetState();
  loopVolumeDown = true;
}

TVController::TVController(IRsend& irsend) :
  irsend{irsend},
  loopArrowUp{false},
  loopArrowDown{false},
  loopArrowLeft{false},
  loopArrowRight{false},
  loopVolumeUp{false},
  loopVolumeDown{false}
{}

void TVController::sendIRSignalsBasedOnState()
{
  if(getLoopArrowUp())
  {
    irsend.sendNikai(TVCodes_ARROW_UP);
    Serial.println("Emitted IR signal based on the value of 'TVCodes_ARROW_UP'.");
    delay(2000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
  if(getLoopArrowDown())
  {
    irsend.sendNikai(TVCodes_ARROW_DOWN);
    Serial.println("Emitted IR signal based on the value of 'TVCodes_ARROW_DOWN'.");
    delay(2000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
  if(getLoopArrowLeft())
  {
    irsend.sendNikai(TVCodes_ARROW_LEFT);
    Serial.println("Emitted IR signal based on the value of 'TVCodes_ARROW_LEFTW_RIGHT'.");
    delay(2000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
  if(getLoopArrowRight())
  {
    irsend.sendNikai(TVCodes_ARROW_RIGHT);
    Serial.println("Emitted IR signal based on the value of 'TVCodes_ARROW_RIGHT'.");
    delay(2000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
  if(getLoopVolumeUp())
  {
    irsend.sendNikai(TVCodes_VOLUME_UP);
    Serial.println("Emitted IR signal based on the value of 'TVCodes_VOLUME_UP'.");
    delay(2000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
  if(getLoopVolumeDown())
  {
    irsend.sendNikai(TVCodes_VOLUME_DOWN);
    Serial.println("Emitted IR signal based on the value of 'TVCodes_VOLUME_DOWN'.");
    delay(2000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
}

void TVController::sendSignalBasedOnUpdateValue(uint8_t value)
{
  switch(value)
  {
    //TV remote commands
    case 1:
      irsend.sendNikai(TVCodes_TOGGLE_ON);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_TOGGLE_ON'.");
      break;
    case 2:
      irsend.sendNikai(TVCodes_MUTE);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_MUTE'.");
      break;
    case 3:
      sendAndRepeatIRSignal(TVCodes_VOLUME_UP, 2, 100);
      break;
    case 4:
      sendAndRepeatIRSignal(TVCodes_VOLUME_DOWN, 2, 100);
      break;
    case 5:
      irsend.sendNikai(TVCodes_ARROW_UP);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_ARROW_UP'.");
      break;
    case 6:
      irsend.sendNikai(TVCodes_ARROW_DOWN);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_ARROW_DOWN'.");
      break;
    case 7:
      irsend.sendNikai(TVCodes_ARROW_LEFT);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_ARROW_LEFT'.");
      break;
    case 8:
      irsend.sendNikai(TVCodes_ARROW_RIGHT);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_ARROW_RIGHT'.");
      break;
    case 9:
      irsend.sendNikai(TVCodes_OK);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_OK'.");
      break;
    case 10:
      irsend.sendNikai(TVCodes_AV);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_AV'.");
      break;
    case 11:
      irsend.sendNikai(TVCodes_HOME);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_HOME'.");
      break;
    case 12:
      irsend.sendNikai(TVCodes_BACK);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_BACK'.");
      break;
    case 13:
      irsend.sendNikai(TVCodes_EXIT);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_EXIT'.");
      break;
    case 14:
      irsend.sendNikai(TVCodes_NETFLIX);
      Serial.println("Emitted IR signal based on the value of 'TVCodes_NETFLIX'.");
      break;
    case 15:
      Serial.println("Resetting tv controller state.");
      resetState();
      break;
    case 16:
      Serial.println("Setting 'loopArrowUp'.");
      setLoopArrowUp();
      break;
    case 17:
      Serial.println("Setting 'loopArrowDown'.");
      setLoopArrowDown();
      break;
    case 18:
      Serial.println("Setting 'loopArrowLeft'.");
      setLoopArrowLeft();
      break;
    case 19:
      Serial.println("Setting 'loopArrowRight'.");
      setLoopArrowRight();
      break;
    case 20:
      Serial.println("Setting 'loopVolumeUp'.");
      setLoopVolumeUp();
      break;
    case 21:
      Serial.println("Setting 'loopVolumeDown'.");
      setLoopVolumeDown();
      break;
    case 22:
      sendAndRepeatIRSignal(TVCodes_VOLUME_UP, 6, 100);
      break;
    case 23:
      sendAndRepeatIRSignal(TVCodes_VOLUME_DOWN, 6, 100);
      break;
      
    default:
      Serial.println("Event registered on 'TV' but no action defined for the incoming callback method argument.");
  }
}

void TVController::sendAndRepeatIRSignal(int code, int numberOfTimes, int delayBetweenSignalsMillis)
{
  for(int i{0}; i < numberOfTimes; ++i)
  {
    irsend.sendNikai(code);
    Serial.print("Emitted IR signal from TVController -> Protocol: Nikai, Code: ");
    Serial.print(code);
    Serial.println();
    delay(delayBetweenSignalsMillis);
  }
}

void TVController::resetState()
{
  loopArrowUp = false;
  loopArrowDown = false;
  loopArrowLeft = false;
  loopArrowRight = false;
  loopVolumeUp = false;
  loopVolumeDown = false;
}

void TVController::printState()
{
  Serial.print("loopArrowUp: ");
  Serial.println(loopArrowUp);
  Serial.print("loopArrowDown: ");
  Serial.println(loopArrowDown);
  Serial.print("loopArrowLeft: ");
  Serial.println(loopArrowLeft);
  Serial.print("loopArrowRight: ");
  Serial.println(loopArrowRight);
  Serial.print("loopVolumeUp: ");
  Serial.println(loopVolumeUp);
  Serial.print("loopVolumeDown: ");
  Serial.println(loopVolumeDown);
}

bool TVController::getLoopArrowUp() { return loopArrowUp; }
bool TVController::getLoopArrowDown() { return loopArrowDown; }
bool TVController::getLoopArrowLeft() { return loopArrowLeft; }
bool TVController::getLoopArrowRight() { return loopArrowRight; }
bool TVController::getLoopVolumeUp() { return loopVolumeUp; }
bool TVController::getLoopVolumeDown() { return loopVolumeDown; }