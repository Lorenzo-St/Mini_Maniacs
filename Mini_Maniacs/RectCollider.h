#pragma once
#include <vector>
#include "Component.h"
#include "GLM.hpp"
#include "Collider.h"

class RectCollider : public Collider
{
public:
  RectCollider()
  {
    width = 1;
    height = 1;
  }
  RectCollider(RectCollider const* r) : width(r->width), height(r->height) {};
  RectCollider* Clone() { return new RectCollider(this); };
  void Read(Stream* s);

  void SetDimensions(float w, float h) { width = w; height = h; };
  glm::vec2 Dimenstions(void) { return { width, height }; }
  
  void CheckCollision(Collider* other);
  constexpr std::string GetName(void) { return __CLASS_NAME__; };

private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { SetType(Rectangle); setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------
  float width;
  float height;
};

