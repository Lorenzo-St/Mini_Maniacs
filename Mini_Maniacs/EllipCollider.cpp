#include "EllipCollider.h"
#include "CollisionFunctions.h"

void EllipCollider::Read(Stream* s) 
{
  // <EllipCollider>
  //  <Radius>
  //   4
  //  <Offset>
  //   0 0
  // </EllipCollider>
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


