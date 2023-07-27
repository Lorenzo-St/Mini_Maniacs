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
  RectCollider* Clone() { return nullptr; };
  void Read(Stream* s);
  void SetDimensions(float w, float h) { width = w; height = h; };
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

