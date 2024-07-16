#include "TVStateHandler.h"
#include <Arduino.h>

TVStateHandler::TVStateHandler(TVController& tvController)
  :
    tvController{tvController},
    tvState{}
{}

void TVStateHandler::handleState()
{
  if(tvState.loopArrowUp)
  {
    tvController.sendArrowUpButtonSignal();
    delay(2000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
  if(tvState.loopArrowDown)
  {
    tvController.sendArrowDownButtonSignal();
    delay(2000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
  if(tvState.loopArrowLeft)
  {
    tvController.sendArrowLeftButtonSignal();
    delay(2000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
  if(tvState.loopArrowRight)
  {
    tvController.sendArrowRightButtonSignal();
    delay(2000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
  if(tvState.loopVolumeUp)
  {
    tvController.sendVolumeUpButtonSignal();
    delay(1000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
  if(tvState.loopVolumeDown)
  {
    tvController.sendVolumeDownButtonSignal();
    delay(1000); //TODO: Set a timeout (associated with the state variable that is used in the if-statement of this block) for which we won't execute the action of this block again until the timeout has passed. In this way we can prevent loop-actions to run too often without having to block the execution of the entire thread.
  }
}

void TVStateHandler::resetState()
{
  tvState.loopArrowUp = false;
  tvState.loopArrowDown = false;
  tvState.loopArrowLeft = false;
  tvState.loopArrowRight = false;
  tvState.loopVolumeUp = false;
  tvState.loopVolumeDown = false;
}

void TVStateHandler::setLoopArrowUp()
{
  resetState();
  tvState.loopArrowUp = true;
}
void TVStateHandler::setLoopArrowDown()
{
  resetState();
  tvState.loopArrowDown = true;
}
void TVStateHandler::setLoopArrowLeft()
{
  resetState();
  tvState.loopArrowLeft = true;
}
void TVStateHandler::setLoopArrowRight()
{
  resetState();
  tvState.loopArrowRight = true;
}
void TVStateHandler::setLoopVolumeUp()
{
  resetState();
  tvState.loopVolumeUp = true;
}
void TVStateHandler::setLoopVolumeDown()
{
  resetState();
  tvState.loopVolumeDown = true;
}