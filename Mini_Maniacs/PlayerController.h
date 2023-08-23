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
    , jumpSpeed(b->jumpSpeed)
    , moveSpeed(b->moveSpeed)
    , fallSpeed(b->fallSpeed)
    , gravity(b->gravity)
  {}
  PlayerController* Clone() { return new PlayerController(this); }


public:
  void OnInit();
  void OnUpdate();
  void OnExit();

  void Read(Stream* s);
  void Write(std::ofstream* s);

  void OnCollision(Entity* other);
private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------

  bool isGrounded = false;
  float jumpSpeed = 0;
  float moveSpeed = 0;
  float fallSpeed = 0;
  glm::vec2 gravity = {0,0};
};