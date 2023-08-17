#include "RectCollider.h"
#include "Stream.h"
#include "CollisionFunctions.h"
#include "Entity.h"
#include "Transform.h"
#include "Physics.h"

void RectCollider::Init() { Static = this->GetParent()->GetComponent<Physics>() == nullptr; }

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
  
    if (token == "<Width>")
      w = s->ReadFloat();
    else if (token == "<Height>")
      h = s->ReadFloat();
    else if (token == "<Line>")
    {
      auto start = s->ReadVector();
      auto end = s->ReadVector();
      addLine(start, end);
    }
    else if (token == "<tileBased>")
      tileBased = s->ReadBool();
    else if (token == "<tileSize>")
      tileSize = s->ReadInt();
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
  else if(other->isType() == Rectangle)
    RectangleCollision(this, other);
}


void RectCollider::OnCollision(Entity* other) 
{
  if (tileBased && !Static) 
  {
    glm::vec2 otherPos = other->GetComponent<Transform>()->GetPosition();
    glm::vec2 thisPos = this->GetParent()->GetComponent<Transform>()->GetPosition();

    RectCollider* otherR = other->GetComponent<RectCollider>();
    glm::vec2 dir = thisPos - otherPos;
    glm::vec2 velo = this->GetParent()->GetComponent<Physics>()->GetVelocity();

    dir.x = (velo.y > velo.x) ? 0: dir.x / std::abs(dir.x);
    dir.y = (velo.x > velo.y) ? 0: dir.y / std::abs(dir.y);


    dir *= 16;
    glm::vec2 nearestTile = otherPos + dir;
    glm::vec2 preserved = (dir.x == 0) ? glm::vec2(thisPos.x, nearestTile.y) : glm::vec2(nearestTile.x, thisPos.y);
    this->GetParent()->GetComponent<Transform>()->SetPosition(preserved);
    std::cout << preserved << std::endl;


  }


}

