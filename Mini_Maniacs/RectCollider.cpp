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
    glm::vec2 preserved = thisPos;
    thisPos = { static_cast<float>(glm::round(glm::round(thisPos.x)/16.0f)) * tileSize, static_cast<float>(glm::round(glm::round(thisPos.y)/tileSize)) * tileSize  };
    RectCollider* otherR = other->GetComponent<RectCollider>();
    glm::vec2 dir = thisPos - otherPos;
    glm::vec2 velo = this->GetParent()->GetComponent<Physics>()->GetVelocity();

    if (velo.x != 0)
      dir = dir;

    dir.x = (std::abs(velo.y) > std::abs(velo.x) && std::abs(dir.y) > std::abs(dir.x)) ? 0: dir.x / std::abs(dir.x != 0 ? dir.x : 1);
    dir.y = (std::abs(velo.x) > std::abs(velo.y) && std::abs(dir.x) > std::abs(dir.y)) ? 0: dir.y / std::abs(dir.y != 0 ? dir.y : 1);

    if (dir == glm::vec2(0, 0))
    {
      dir = thisPos - otherPos;
      dir.x = (std::abs(dir.y) > std::abs(dir.x)) ? 0 : dir.x / std::abs(dir.x != 0 ? dir.x : 1);
      dir.y = (std::abs(dir.x) > std::abs(dir.y)) ? 0 : dir.y / std::abs(dir.y != 0 ? dir.y : 1);
    }
    if (dir.x * dir.x == 1 && dir.y * dir.y == 1)
      return;
    dir *= otherR->tileSize;
    glm::vec2 nearestTile = otherPos + dir;
    preserved = (dir.x == 0) ? glm::vec2(preserved.x, nearestTile.y) : glm::vec2(nearestTile.x, preserved.y);

    if (preserved.y <= -16)
      std::cout << "AAAAAAAAAAAAAAAAAAAA";

    this->GetParent()->GetComponent<Transform>()->SetPosition(preserved);
    //this->GetParent()->GetComponent<Physics>()->SetVelocity(velo);
    std::cout << preserved << "\n";
    std::cout << velo << "\n";
    std::cout << "---------------" << std::endl;



  }


}

