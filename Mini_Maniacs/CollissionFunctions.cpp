#include <iostream>
#include "RectCollider.h"
#include "EllipCollider.h"
#include "Collider.h"
#include "CollisionFunctions.h"
#include "Entity.h"
#include "Transform.h"
#include "Physics.h"
#include "CollisionLedger.h"

#define DRAW_DEBUG_LINES 0
#define DEBUG_WRITING 0
#if _DEBUG && DRAW_DEBUG_LINES
#include "Render API.h"
#endif 
typedef struct line 
{
  glm::vec2 point1;
  glm::vec2 point2;
}line;

void RectangleCollision(Collider* rect1, Collider* rect2)
{

  glm::vec2 OldPosition = rect1->GetParent()->GetComponent<Physics>()->GetOldPosition();
  glm::vec2 NewPosition = rect1->GetParent()->GetComponent<Transform>()->GetPosition();
  glm::vec2 WallPos = rect2->GetParent()->GetComponent<Transform>()->GetPosition();
  RectCollider* mover = static_cast<RectCollider*>(rect1);
  RectCollider* wall = static_cast<RectCollider*>(rect2);

  bool xCol = false;
  bool yCol = false;
  glm::vec2 MOffset(mover->Width() / 2.0f, mover->Height() / 2.0f);
  glm::vec2 WOffset(mover->Width() / 2.0f, mover->Height() / 2.0f);

  float xMove = 0;
  float yMove = 0;

  if (std::abs(NewPosition.x - WallPos.x) > MOffset.x + WOffset.x) return;
  if (std::abs(NewPosition.y - WallPos.y) > MOffset.y + WOffset.y) return;

  float d = (NewPosition.x - WallPos.x > NewPosition.y - WallPos.y) ? NewPosition.x - WallPos.x : NewPosition.y - WallPos.y;

  glm::vec2 moveVec = NewPosition - OldPosition;

  float ti = -(OldPosition.x / moveVec.x); // Y Intersept Time
  if (isinf(ti) || isnan(ti))
    ti = 1000000000.0f * -(moveVec.y / std::abs(moveVec.y));

  float b = OldPosition.y + (ti * moveVec.y); // Y intersept
  float m = moveVec.y / moveVec.x;
  if (isinf(m) || isnan(m))
    m = 1000000000.0f * (moveVec.y / std::abs(moveVec.y));

  float rootInside = -(b * b)
    - (2 * b * OldPosition.x * m)
    + (2 * b * OldPosition.y)
    - ((OldPosition.x * OldPosition.x) * (m * m))
    + (2 * OldPosition.x * OldPosition.y * m)
    - OldPosition.y * OldPosition.y
    + (m * m) * (d * d)
    + d * d;

  float rootOutside = -b * m + OldPosition.x + OldPosition.y * m;
  float denom = m * m + 1;

  float x1 = -(std::sqrtf(rootInside) + rootOutside) / denom;
  float x2 = (std::sqrtf(rootInside) + rootOutside) / denom;

  float t1 = (x1 - OldPosition.x) / moveVec.x;
  float t2 = (x2 - OldPosition.x) / moveVec.x;



  //rect1->GetParent()->GetComponent<Transform>()->SetPosition(intersect);
  //glm::vec2 preserved = { 1 * yCol == true, 1 * xCol == true };
  //rect1->GetParent()->GetComponent<Physics>()->SetVelocity(rect1->GetParent()->GetComponent<Physics>()->GetVelocity() * preserved);

  //std::cout << "Collision: " << intersect <<"\n";
  //std::cout << std::endl;
  CollisionLedger::AddInteraction({ rect1->GetParent(), rect2->GetParent() });



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
    Ellip1->GetParent()->GetComponent<Transform>()->SetPosition(closestPoint);
  }
  else if (distance < minDist) 
  {
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
