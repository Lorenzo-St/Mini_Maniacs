#include "RectCollider.h"
#include "Stream.h"
#include "CollisionFunctions.h"
#include "Entity.h"
#include "Transform.h"
#include "Physics.h"


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
    if (token == "<Collider>")
      this->Collider::Read(s);
    else if (token == "<Width>")
      w = s->ReadFloat();
    else if (token == "<Height>")
      h = s->ReadFloat();
    else if (token == "</RectCollider>")
      break;
  }
  

};

void RectCollider::Write(std::ofstream* s) 
{
  *s << "<RectCollider>\n";
  Collider::Write(s);
  *s << "<Width>\n";
  *s << w << "\n";
  *s << "<Height>\n";
  *s << h << "\n";
  *s << "</RectCollider>\n";

   
}



void RectCollider::CheckCollision(Collider* other)
{
  if (other->isType() == Circle) 
  {
    RectEllipCollision(this, other);
  }
  else if(other->isType() == Rectangle)
    RectangleCollision(this, other);
}


void RectCollider::OnCollision(Entity* other) 
{


}

