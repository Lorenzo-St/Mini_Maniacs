#pragma once
#include "Component.h"
#include <glm.hpp>
static std::ostream& operator<<(std::ostream& o, glm::vec2 vec)
{
  o << "( " << vec.x << " ," << vec.y << " )";
  return o;
}


class Transform : public Component
{
public:
  Transform() : pos(0), scale(0), rot(0) {};
  Transform(Transform const* t) { pos = t->pos; scale = t->scale; rot = t->rot; };
  Transform* Clone() { return new Transform(this); };

  void Read(Stream* s);
  void Update(void);
  

  glm::vec2 const& GetPosition(void) { return pos; };

  glm::vec2 const& GetScale(void) { return scale; };
  float GetRotation(void) { return rot; }

  void SetPosition(glm::vec2 const& position) { pos = position; }

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

  glm::vec2 scale = {};
  float rot = 0;
};
