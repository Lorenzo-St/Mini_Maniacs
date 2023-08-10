#pragma once
#include "Behavior.h"
#include "Stream.h"

class PlayerController : Behavior
{
  enum States
  {

  };
  PlayerController() = default;
  PlayerController(PlayerController const* b)
    : Behavior(b)
  {}
  PlayerController* Clone() { return new PlayerController(this); }


public:
  void OnInit();
  void OnUpdate();
  void OnExit();

  void Read(Stream* s);

private:

};