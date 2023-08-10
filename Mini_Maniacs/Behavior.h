#pragma once
#include "Component.h"

class Behavior : public Component
{
public:
  Behavior()
  {

  }
  void Init();
  void Update();
  void Exit();  
  Behavior(Behavior const* b);
  Behavior* Clone() { return new Behavior(this); };
  void Read(Stream* s) { };
private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------
  int currentState;
  int nextState;

};
