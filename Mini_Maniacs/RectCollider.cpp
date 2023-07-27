#include "RectCollider.h"
#include "Stream.h"
#include "CollisionFunctions.h"

void RectCollider::Read(Stream* s)
{ 
  // <RectCollider>
  //  <line>
  //   1.0
  //   2.0
  //   2.0
  //   3.0
  //  <point>
  // 
  // </RectCollider>
  
  
  while (true) 
  {
    std::string token = s->ReadString();
  
    if (token == "<Line>")
      addLine(s->ReadVector(), s->ReadVector());
    else if (token == "</RectCollider>")
      break;
  }
  

};



void RectCollider::CheckCollision(Collider* other)
{
  if (other->isType() == Circle) 
  {
    RectEllipCollision(this, other);
  }
}

