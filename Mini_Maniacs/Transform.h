#pragma once
#include "Component.h"
#include <glm.hpp>

class Transform : public Component
{
public:
  Transform() : pos(0), OldPosition(0), velocity(0), acceleration(0), scale(0), rot(0), drag(1) {};
  Transform(Transform const* t) { pos = t->pos; velocity = t->velocity; acceleration = t->acceleration; drag = t->drag; scale = t->scale; rot = t->rot; };
  Transform* Clone() { return new Transform(this); };

  void Read(Stream* s);
  void Update(void);
  

  glm::vec2 const& GetPosition(void) { return pos; };
  glm::vec2 const& GetOldPosition(void) { return OldPosition; };
  glm::vec2 const& GetVelocity(void) { return velocity; };
  glm::vec2 const& GetAcceleration(void) { return acceleration; };
  glm::vec2 const& GetScale(void) { return scale; };
  float GetRotation(void) { return rot; }
  float GetDrag(void) { return drag; }

  void SetPosition(glm::vec2 const& position) { pos = position; }
  void SetVelocity(glm::vec2 const& velo) { velocity = velo; }
  void AddVelocity(glm::vec2 const& add) { velocity += add; }
  void SetAcceleration(glm::vec2 const& accel) { acceleration = accel; }
  void SetAcceleration(glm::vec2 const& accel, float dragPerc) { acceleration = accel; drag = 1 - dragPerc; }
  void SetScale(glm::vec2 const& scal) { scale = scal; }
  void SetRotation(float rotation) { rot = rotation; }



private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------

  glm::vec2 pos = {};
  glm::vec2 OldPosition = {};
  glm::vec2 velocity = {};
  glm::vec2 acceleration = {};
  glm::vec2 scale = {};
  float rot = 0;
  float drag = 1;
};
