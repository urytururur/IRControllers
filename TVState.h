#pragma once

struct TVState
{
  bool loopArrowUp;
  bool loopArrowDown;
  bool loopArrowLeft;
  bool loopArrowRight;
  bool loopVolumeUp;
  bool loopVolumeDown;

  TVState() :
    loopArrowUp{false},
    loopArrowDown{false},
    loopArrowLeft{false},
    loopArrowRight{false},
    loopVolumeUp{false},
    loopVolumeDown{false}
  {}
};