#pragma once
#include "Component.h"
#include <glm.hpp>

class Transform : public Component
{
public:
  Transform() = default;
  Transform(Transform const* t) { pos = t->pos; velocity = t->velocity; acceleration = t->acceleration; drag = t->drag; };
  Transform* Clone() { return new Transform(this); };

  void Read(Stream* s);
  void Update(void);

  glm::vec2 const& GetPosition(void) { return pos; };
  glm::vec2 const& GetVelocity(void) { return velocity; };
  glm::vec2 const& GetAcceleration(void) { return acceleration; };
  float GetDrag(void) { return drag; }

  void SetPosition(glm::vec2 const& position) { pos = position; }
  void SetVelocity(glm::vec2 const& velo) { velocity = velo; }
  void SetAcceleration(glm::vec2 const& accel) { acceleration = accel; }
  void SetAcceleration(glm::vec2 const& accel, float dragPerc) { acceleration = accel; drag = 1 - dragPerc; }

  
private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------

  glm::vec2 pos = {};
  glm::vec2 velocity = {};
  glm::vec2 acceleration = {};
  float drag = 1;
};
