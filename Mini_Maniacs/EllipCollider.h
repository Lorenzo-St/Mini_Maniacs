#pragma once
#include "Collider.h"
#include <glm.hpp>
class EllipCollider : public Collider
{
public:
  EllipCollider() { }
  EllipCollider(EllipCollider const* r) : Collider(r), radius(r->radius), offset(r->offset) {  };
  EllipCollider* Clone() { return new EllipCollider(this); };
  void Read(Stream* s);

  void SetRadius(float r) { radius = r; }
  float GetRadius(void) { return radius; }
 
  void SetOffset(glm::vec2 const& o) { offset = o; }
  glm::vec2 const& GetOffset(void) { return offset; }

  void CheckCollision(Collider* other);

private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { SetType(Circle); return true; };
  const bool s = set();
  // -------------------------

  float radius = 1;
  glm::vec2 offset = {0,0};
};
