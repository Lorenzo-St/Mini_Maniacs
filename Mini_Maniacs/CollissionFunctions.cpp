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
  if (glm::distance(NewPosition, WallPos) > glm::distance(WallPos, {WallPos.x + wall->Width()/2.0f, WallPos.y + wall->Height()/2.0f}))
    return;
  glm::vec2 dir = glm::normalize(OldPosition - WallPos);

  float xDis = NewPosition.x - WallPos.x;
  float yDis = NewPosition.y - WallPos.y;
  if (xDis > yDis && xDis < mover->Width() + wall->Width())
  {
    glm::vec2 xMove(dir.x , 0);
    xMove = glm::normalize(xMove) * xDis;
    NewPosition = NewPosition + xMove;
    xCol = true;
  }
  if (yDis > xDis && yDis < mover->Height() + wall->Height())
  {
    glm::vec2 yMove(0,dir.y);
    yMove = glm::normalize(yMove) * yDis;
    NewPosition = NewPosition + yMove;
    yCol = true;
  }
 
  if (xCol || yCol) 
  {
    std::cout << "inter" << "\n";
    std::cout << NewPosition << "\n";
    std::cout << WallPos << "\n";
    std::cout << "---------------------" << std::endl;
    rect1->GetParent()->GetComponent<Transform>()->SetPosition(NewPosition);
    CollisionLedger::AddInteraction({ rect1->GetParent(), rect2->GetParent() });

  }


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
