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
  RectCollider(RectCollider const* r): w(r->w), h(r->h) { linesSegments = r->linesSegments; };
  RectCollider* Clone() { return new RectCollider(this); };
  void Read(Stream* s);

  void addLine(glm::vec2 start, glm::vec2 end) { linesSegments.push_back({ start, end }); }

  float Width() { return w; }
  float Height() { return h; }
  void CheckCollision(Collider* other);

  void OnCollision(Entity* other);

  std::vector<std::array<glm::vec2, 2>> const& getSegments(void) { return linesSegments; }
private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { SetType(Rectangle); return true; };
  const bool s = set();
  // -------------------------
  float w, h;
  bool tileBased = true;
  int tileSize = 16;
  std::vector<std::array<glm::vec2, 2>> linesSegments;
  
};

