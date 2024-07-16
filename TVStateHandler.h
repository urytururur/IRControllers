#pragma once
#include "TVController.h"
#include "TVState.h"

class TVStateHandler
{
private:
  TVController& tvController;
  TVState tvState;

public:
  TVStateHandler(TVController& tvController);

  void handleState();
  void resetState();
  void setLoopArrowUp();
  void setLoopArrowDown();
  void setLoopArrowLeft();
  void setLoopArrowRight();
  void setLoopVolumeUp();
  void setLoopVolumeDown();
};