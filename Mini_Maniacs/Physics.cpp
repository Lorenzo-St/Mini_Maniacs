#include <string>
#include <glm.hpp>
#include "Physics.h"
#include "Stream.h"
#include "Entity.h"
#include "Transform.h"
#include "EllipCollider.h"
#include "Time.h"
void Physics::Update(void) 
{
  Transform& t = *GetParent()->GetComponent<Transform>();

  if (doGravity) 
  {
    t.SetAcceleration(Gravity);
  }

  t.AddVelocity(t.GetAcceleration() * Time.deltaTime() * t.GetDrag());
  t.SetPosition(t.GetVelocity() * Time.deltaTime());


#if _DEBUG && 1
  std::cout << "Pos: " << t.GetPosition() << std::endl;
  std::cout << "Velo: " << t.GetVelocity() << std::endl;

  //std::cout << "Scale: " << scale.x << "," << scale.y << std::endl;
  //std::cout << "Rot: " << rot << std::endl;
#endif

#if _DEBUG && 0
  if (pos.y < -200)
  {
    OldPosition.y = 500;
    pos.y = 500;

  }
#endif


}

void Physics::Read(Stream* s) 
{
  // <Physics>
  //  <DoesGravity>
  //   true
  //  <Weight>
  //   1
  //  <Body>
  //   0
  //  <Gravity>
  //   0
  //  -9.8
  // </Physics>
  //
  //
  std::string token;
  while (true) 
  {
    token = s->ReadString();
    if (token == "<DoesGravity>")
      doGravity = s->ReadBool();
    else if (token == "<Weight>")
      weight = s->ReadFloat();
    else if (token == "<Body>")
      body = static_cast<bodyType>(s->ReadInt());
    else if (token == "<Gravity>")
      Gravity = s->ReadVector();
    else if (token == "</Physics>")
      break;
  }




}

