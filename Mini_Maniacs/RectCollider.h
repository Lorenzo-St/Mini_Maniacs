#pragma once
#include <array>
#include <vector>
#include "Component.h"
#include "GLM.hpp"
#include "Collider.h"

class RectCollider : public Collider
{
public:
  RectCollider() { }
  RectCollider(RectCollider const* r): w(r->w), h(r->h) {  };
  RectCollider* Clone() { return new RectCollider(this); };
  void Read(Stream* s);


  void CheckCollision(Collider* other);

private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { SetType(Rectangle); return true; };
  const bool s = set();
  // -------------------------
  float w, h;
  
};

