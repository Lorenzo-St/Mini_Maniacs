#pragma once
#include "Behavior.h"
#include "Stream.h"

class Behavior_Template : Behavior
{
  enum States
  {
    
  };
public:
  Behavior_Template() = default;
  Behavior_Template(Behavior_Template const* b)
    : Behavior(b)
  {}
  Behavior_Template* Clone() { return new Behavior_Template(this); }


public:
  void OnInit();
  void OnUpdate();
  void OnExit();

  void Read(Stream* s);

private:

};