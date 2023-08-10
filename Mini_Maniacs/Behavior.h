#pragma once
#include "Component.h"
#include <utility>
class Behavior : public Component
{
public:
  Behavior()
  {

  }
  Behavior* Clone() { return new Behavior(this); };
  Behavior(Behavior const* b) 
    : currentState(b->currentState)
    , nextState(b->nextState)
    , stateTimer(b->stateTimer)
    , stateLength(b->stateLength)
  {};

  void Init();
  void Update();
  void Exit();  

  virtual void OnInit() {};
  virtual void OnUpdate() {};
  virtual void OnStateChange() {};
  virtual void OnExit() {};
  virtual void Read(Stream* s) {};
private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------
  int currentState;
  int nextState;

  float stateTimer;
  float stateLength;

};
