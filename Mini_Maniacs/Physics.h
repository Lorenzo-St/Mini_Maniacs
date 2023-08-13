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
  
  glm::vec2 const& getGravity(void) { return Gravity;};

  bool DoesGravity(void) { return doGravity; }
  float GetWeight(void) { return weight; }
  bodyType GetBodyType(void) { return body; }

  glm::vec2 const& GetOldPosition(void) { return oldPos; };
  glm::vec2 const& GetVelocity(void) { return velocity; };
  glm::vec2 const& GetAcceleration(void) { return acceleration; };
  float GetDrag(void) { return drag; }

  void SetVelocity(glm::vec2 const& velo) { velocity = velo; }
  void AddVelocity(glm::vec2 const& add) { velocity += add; }
  void SetAcceleration(glm::vec2 const& accel) { acceleration = accel; }
  void SetAcceleration(glm::vec2 const& accel, float dragPerc) { acceleration = accel; drag = 1 - dragPerc; }

private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------

  glm::vec2 oldPos = {};
  glm::vec2 velocity = {};
  glm::vec2 acceleration = {};
  float drag = 1;

  bool doGravity = true;
  bodyType body = Rigid;
  float weight = 1;
  glm::vec2 Gravity = {0, -9.8f};

};
