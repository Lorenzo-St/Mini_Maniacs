#pragma once
#include "Behavior.h"
#include "Stream.h"

class PlayerController : public Behavior
{
private:
  enum States
  {

  };
public:
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
  void OnCollision(Entity* other);
private:
  bool isGrounded = false;
  float jumpSpeed = 0;
};