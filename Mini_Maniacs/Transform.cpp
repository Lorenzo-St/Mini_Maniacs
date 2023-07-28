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
  while (true)
  {

    std::string token = s->ReadString();
    if (token == "<Position>")
      pos = s->ReadVector();
    else if (token == "<Velocity>")
      velocity = s->ReadVector();
    else if (token == "<Acceleration>")
      acceleration = s->ReadVector();
    else if (token == "<Scale>")
      scale = s->ReadVector();
    else if (token == "<Rotation>")
      rot = s->ReadFloat();
    else if (token == "<Drag>")
      drag = s->ReadFloat();
    else if (token == "</Transform>")
      break;
  }
}

void Transform::Update(void)
{
  OldPosition = pos;
  velocity += acceleration * Time.deltaTime() * drag;
  pos += velocity * Time.deltaTime();
#if _DEBUG && 0
  std::cout << "Pos: " << pos.x << "," << pos.y << std::endl;
  std::cout << "Scale: " << scale.x << "," << scale.y << std::endl;
  std::cout << "Rot: " << rot << std::endl;
#endif

#if _DEBUG && 1
  if (pos.y < -200)
    pos.y = 300;
#endif
}


