#include "Transform.h"
#include "Time.h"
#include "Stream.h"
#if _DEBUG
#include <iostream>
#endif
void Transform::Read(Stream* s) 
{
  // In file order, 
  // <Transform>
  //   <Position>
  //     3.14159
  //     0.5772156649
  //   <Velocity>
  //     1.0
  //     2.5
  //   <Acceleration>
  //     0.0
  //     0.0
  //   <Drag>
  //     0.0
  // <Next Component>
  std::string token = s->ReadString();
  if (token == "<Position>")
  {
    pos = s->ReadVector();
    token = s->ReadString();
  }
  if (token == "<Velocity>") 
  {
    velocity = s->ReadVector();
    token = s->ReadString();
  }
  if (token == "<Acceleration>")
  {
    acceleration = s->ReadVector();
    token = s->ReadString();
  }
  if (token == "<Drag>")
  {
    drag = s->ReadFloat();
    token = s->ReadString();
  }
}

void Transform::Update(void)
{
  velocity += acceleration * Time.deltaTime() * drag;
  pos += velocity * Time.deltaTime();
#if _DEBUG
  std::cout << pos.x << "," << pos.y << std::endl;
#endif
}


