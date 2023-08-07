#include "EllipCollider.h"
#include "CollisionFunctions.h"
#include "Stream.h"

void EllipCollider::Read(Stream* s) 
{
  // <EllipCollider>
  //  <Radius>
  //   4
  //  <Offset>
  //   0 0
  // </EllipCollider>

  while (true)
  {
    std::string token = s->ReadString();

    if (token == "<Radius>")
    {
      radius = s->ReadFloat();
    }
    else if (token == "<Offset>")
    {
      offset = s->ReadVector();
    }
    else if (token == "</RectCollider>")
      break;
  }

}

void EllipCollider::CheckCollision(Collider* other)
{
  if (other->isType() == Rectangle)
  {
    RectEllipCollision(other, this);
  }
  else if (other->isType() == Circle)
    CircleCollision(this, other);
}


