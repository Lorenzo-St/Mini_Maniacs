#pragma once
#include "Component.h"
#include "GLM.hpp"
class Collider : public Component
{
public:
  enum type 
  {
    Rectangle,
    Circle,
    Strange
  };
  Collider() = default;
  Collider* Clone() { return new Collider(this); };
  Collider(Collider const* c) { ColliderType = c->ColliderType; }
  void Read(Stream* s) {};
  constexpr void SetType(type t) { ColliderType = t; }
  virtual void CheckCollision(Collider* other) {};
  type isType(void) { return ColliderType; }

private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------
  type ColliderType;
  // void AddColliderVertex(glm::vec2 localPos) {};
  // std::vector<glm::vec2> RectPoints;

};


