#include "Component.h"
#include <glm.hpp>

class Physics : public Component
{
public:
  enum bodyType 
  {
    Rigid,
    Soft // Not now
  };

  Physics() = default;
  Physics(Physics const* p) : doGravity(p->doGravity), body(p->body), weight(p->weight), Gravity(p->Gravity) {};
  Physics* Clone() { return new Physics(this); };
  
  void Read(Stream* s);
  void Update(void);

  void setGravity(float g) { Gravity = { 0, g }; }
  void setGravity(glm::vec2 g) { Gravity = g; }


  bool DoesGravity(void) { return doGravity; }
  float GetWeight(void) { return weight; }
  bodyType GetBodyType(void) { return body; }

private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------
  bool doGravity = true;
  bodyType body = Rigid;
  float weight = 1;
  glm::vec2 Gravity = {0, -9.8};

};
