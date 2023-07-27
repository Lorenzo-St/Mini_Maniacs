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
  Collider* Clone() = 0;
  void Read(Stream* s) = 0;
  constexpr void SetType(type t) { ColliderType = t; }
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


