#include <iostream>
#include <numeric>

#include "RectCollider.h"
#include "EllipCollider.h"
#include "Collider.h"
#include "CollisionFunctions.h"
#include "Entity.h"
#include "Transform.h"
#include "Physics.h"
#include "CollisionLedger.h"

#define DRAW_DEBUG_LINES 0
#define DEBUG_WRITING 1
#if _DEBUG && DRAW_DEBUG_LINES
#include "Render API.h"
#endif 
typedef struct line 
{
  glm::vec2 point1;
  glm::vec2 point2;
}line;

bool PointCollideRect(glm::vec2 point, RectCollider* rect) 
{
  glm::vec2 WallPos = rect->GetParent()->GetComponent<Transform>()->GetPosition();

  if (std::abs(point.x - WallPos.x) >= rect->Width() /2.0f) return false;
  if (std::abs(point.y - WallPos.y) >= rect->Height() / 2.0f) return false;
  return true;
}



void RectangleCollision(Collider* rect1, Collider* rect2) 
{

  glm::vec2 OldPosition = rect1->GetParent()->GetComponent<Physics>()->GetOldPosition();
  glm::vec2 NewPosition = rect1->GetParent()->GetComponent<Transform>()->GetPosition();
  glm::vec2 WallPos = rect2->GetParent()->GetComponent<Transform>()->GetPosition();
  RectCollider* mover = static_cast<RectCollider*>(rect1);
  RectCollider* wall  = static_cast<RectCollider*>(rect2);
  
  glm::vec2 MOffset(mover->Width() / 2.0f, mover->Height() / 2.0f);
  glm::vec2 WOffset(mover->Width() / 2.0f, mover->Height() / 2.0f);
  if (std::abs(NewPosition.x - WallPos.x) >= MOffset.x + WOffset.x) return;
  if (std::abs(NewPosition.y - WallPos.y) >= MOffset.y + WOffset.y) return;
  CollisionLedger::AddInteraction({ rect1->GetParent(), rect2->GetParent() });
  if (rect1->IsTrigger() || rect2->IsTrigger()) 
  {
    //std::cout << "Trigger Collision" << std::endl;
    return;
  }
  glm::vec2 preserved = NewPosition;
  glm::vec2 moveVec = (NewPosition - OldPosition);

  if (moveVec.x != 0) 
  {
    preserved.x = WallPos.x + ((WOffset.x + MOffset.x) * ((moveVec.x < 0) ? -1 : 1));
  }
  rect1->GetParent()->GetComponent<Transform>()->SetPosition(preserved);
  if (std::abs(NewPosition.x - WallPos.x) >= MOffset.x + WOffset.x) return;
  if (std::abs(NewPosition.y - WallPos.y) >= MOffset.y + WOffset.y) return;
  preserved.x = NewPosition.x;
  if (moveVec.y != 0)
  {
    preserved.y = WallPos.y + ((WOffset.y + MOffset.y) * ((moveVec.y < 0) ? 1.f : -1.f));
  }
  rect1->GetParent()->GetComponent<Transform>()->SetPosition(preserved);




#if _DEBUG && DRAW_DEBUG_LINES
  glm::vec2 scale = rect1->GetParent()->GetComponent<Transform>()->GetVelocity();
  if (earliestTime < 1)
    scale *= earliestTime;
  glm::vec2 posi = (OldPosition + (scale/2.0f));
  scale = glm::abs(scale);
  if (scale.x == 0)
    scale.x = 1;
  if (scale.y == 0)
    scale.y = 1;
  
  api.DrawRect(posi, scale);
#endif 

}

void CircleCollision(Collider* Ellip1, Collider* Ellip2) 
{


  EllipCollider* ellip1 = static_cast<EllipCollider*>(Ellip1);
  EllipCollider* ellip2 = static_cast<EllipCollider*>(Ellip2);

  glm::vec2 startPos = Ellip1->GetParent()->GetComponent<Physics>()->GetOldPosition();
  glm::vec2 endPos = Ellip1->GetParent()->GetComponent<Transform>()->GetPosition();

  glm::vec2 ellip2Pos = Ellip2->GetParent()->GetComponent<Transform>()->GetPosition();

  float minDist = ellip1->GetRadius() + ellip2->GetRadius();
  if (glm::distance(startPos, ellip2Pos) > minDist && glm::distance(endPos, ellip2Pos) > minDist)
    return;
  glm::vec2 moveVec = endPos - startPos;
  glm::vec2 toEllip2 = ellip2Pos - startPos;
  if (glm::dot(toEllip2, moveVec) < 0)
    return;
  glm::vec2 projection = (glm::dot(toEllip2, moveVec) / glm::dot(moveVec, moveVec)) * moveVec;
  if (glm::distance(startPos, projection) > glm::length(moveVec))
    projection = moveVec;
  glm::vec2 closestPoint = startPos + projection;

  float distance = glm::distance(closestPoint, ellip2Pos);


  if (distance == minDist) 
  {
    if (Ellip1->IsTrigger() || Ellip2->IsTrigger())
    {
      CollisionLedger::AddInteraction({ Ellip1->GetParent(), Ellip2->GetParent() });
      return;
    }
    Ellip1->GetParent()->GetComponent<Transform>()->SetPosition(closestPoint);
  }
  else if (distance < minDist) 
  {
    if (Ellip1->IsTrigger() || Ellip2->IsTrigger())
    {
      CollisionLedger::AddInteraction({ Ellip1->GetParent(), Ellip2->GetParent() });
      return;
    }
    //std::cout << "hi interacted" << std::endl;
    glm::vec2 staticToClosest = closestPoint - ellip2Pos;
    glm::vec2 CCRot = { -staticToClosest.y,  staticToClosest.x };
    glm::vec2 CRot  = {  staticToClosest.y, -staticToClosest.x };
    float len = std::sqrtf((minDist * minDist) - (distance * distance));
    // Select which rotation will move the closest point closer to the starting point, 
    // in no circum stance should an object moving on 
    // a straight line end up futher from it starting position if it collided with something
    glm::vec2 workingRot = (glm::dot(CCRot, moveVec) < glm::dot(CRot, moveVec)) ? CRot : CCRot;
    workingRot = glm::normalize(workingRot);
    glm::vec2 offSetVector = workingRot * len;
    Ellip1->GetParent()->GetComponent<Transform>()->SetPosition(closestPoint + offSetVector);

    CollisionLedger::AddInteraction({ ellip1->GetParent(), ellip1->GetParent() });

    std::cout << "Moved To: " << closestPoint.x + offSetVector.x << "," << closestPoint.y + offSetVector.y << std::endl;
  }
}

void RectEllipCollision(Collider* rect1, Collider* Ellips2) 
{
  // TODO much later, This is really fucking hard to do without cheesing it
  // and I don't want to cheese it
}
