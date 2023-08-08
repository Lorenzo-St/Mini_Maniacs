#include <string>
#include <glm.hpp>
#include "Physics.h"
#include "Stream.h"
#include "Entity.h"
#include "Transform.h"
#include "EllipCollider.h"
void Physics::Update(void) 
{
  if (doGravity) 
  {
    GetParent()->GetComponent<Transform>()->SetAcceleration(Gravity);
  }
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

