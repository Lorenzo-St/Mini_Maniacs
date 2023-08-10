#pragma once
#include "Behavior.h"
#include "Stream.h"

class PlayerMotor : Behavior
{
  enum States
  {

  };
  PlayerMotor() = default;
  PlayerMotor(PlayerMotor const* b)
    : Behavior(b)
  {}
  PlayerMotor* Clone() { return new PlayerMotor(this); }


public:
  void OnInit();
  void OnUpdate();
  void OnExit();

  void Read(Stream* s);

private:

};