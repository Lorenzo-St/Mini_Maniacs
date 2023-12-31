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
  if (doGravity) 
  {
    acceleration = Gravity;
  }
  oldPos = this->GetParent()->GetComponent<Transform>()->GetPosition();
  velocity += acceleration * Time.deltaTime() * drag;
  this->GetParent()->GetComponent<Transform>()->SetPosition(oldPos + (velocity * Time.deltaTime()));


#if _DEBUG && 0
  std::cout << "Pos: " << oldPos << std::endl;
  std::cout << "Velo: " << velocity << std::endl;
  std::cout << "Accel: " << acceleration << std::endl;

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

void Physics::Write(std::ofstream* s)
{
  *s << "<Physics>\n  ";
  *s << "<DoesGravity>\n   ";
  *s << doGravity << "\n  ";
  *s << "<Weight>\n   ";
  *s << weight << "\n  ";
  *s << "<Velocity>\n   ";
  *s << velocity << "\n  ";
  *s << "<Acceleration>\n   ";
  *s << acceleration << "\n  ";
  *s << "<Drag>\n   ";
  *s << drag << "\n  ";
  *s << "<Body>\n   ";
  *s << body << "\n  ";
  *s << "<Gravity>\n   ";
  *s << Gravity << "\n ";
  *s << "</Physics>\n ";
};




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
    else if (token == "<Velocity>")
      velocity = s->ReadVector();
    else if (token == "<Acceleration>")
      acceleration = s->ReadVector();
    else if (token == "<Drag>")
      drag = s->ReadFloat();
    else if (token == "<Body>")
      body = static_cast<bodyType>(s->ReadInt());
    else if (token == "<Gravity>")
      Gravity = s->ReadVector();
    else if (token == "</Physics>")
      break;
  }




}

