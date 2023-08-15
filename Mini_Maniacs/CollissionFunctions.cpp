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
  RectCollider* wall  = static_cast<RectCollider*>(rect2);
  
  float earliestTime = 2;
  glm::vec2 earliestMove = { 0,0 };
  int dir = 1;
  // Check line collision along the movement for each point, if there is any collision then the rects collided
  for (auto& l : mover->getSegments()) 
  {
    glm::vec2 startpos = OldPosition + l[0];
    glm::vec2 endpos = NewPosition + l[1];
    glm::vec2 moveVec = endpos - startpos;
    for (auto segment : wall->getSegments()) 
    {
      segment[0] += WallPos;
      segment[1] += WallPos;
      glm::vec2 wallVec = segment[1] - segment[0];
      glm::vec2 wallNorm = { wallVec.y, -wallVec.x };
      wallNorm = glm::normalize(wallNorm);
      if (glm::dot(moveVec, wallNorm) == 0)
        continue;
      if (glm::dot(wallNorm, startpos) < glm::dot(wallNorm, segment[0]) && glm::dot(wallNorm, endpos) < glm::dot(wallNorm, segment[1]))
        continue;
      if (glm::dot(wallNorm, startpos) >= glm::dot(wallNorm, segment[0]) && glm::dot(wallNorm, endpos) > glm::dot(wallNorm, segment[1]))
        continue;

      float ti = glm::dot(wallNorm, segment[0]) - glm::dot(wallNorm, startpos);
      ti /= glm::dot(wallNorm, moveVec);

      glm::vec2 intersection = startpos + (moveVec * ti);

      glm::vec2 testVector = intersection - segment[0];
      if (glm::dot(wallVec, testVector) < 0)
        continue;
      wallVec = segment[0] - segment[1];
      testVector = intersection - segment[1];
      if (glm::dot(wallVec, testVector) < 0)
        continue;
      if (ti <= earliestTime)
      {
        moveVec = NewPosition - OldPosition;
        
        glm::vec2 toOther = (OldPosition + (moveVec * ti)) - WallPos;
        toOther = glm::normalize(toOther);
        if (toOther.x == toOther.y)
          dir = 1;
        else if (toOther.y > toOther.x)
          dir = 1;
        else if (toOther.x > toOther.y)
          dir = 0;
        earliestTime = ti;
        earliestMove = moveVec;
      }
    }    
  }
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



  if (earliestTime < 1)
  {
    
    glm::vec2 moveVec = NewPosition - OldPosition;
#if _DEBUG && DEBUG_WRITING
    std::cout << "moveVec: " << moveVec.x << ", " << moveVec.y << std::endl;
    std::cout << "earliestMove: " << earliestMove.x << ", " << earliestMove.y << std::endl;
#endif
    glm::vec2 intersection = OldPosition + (earliestMove * earliestTime);
    if (dir == 1) 
    {
      intersection.x = NewPosition.x;
      rect1->GetParent()->GetComponent<Physics>()->SetVelocity({ rect1->GetParent()->GetComponent<Physics>()->GetVelocity().x, 0 });
    }
    else if (dir == 0) 
    {
      intersection.y = NewPosition.y;
      rect1->GetParent()->GetComponent<Physics>()->SetVelocity({ 0,rect1->GetParent()->GetComponent<Physics>()->GetVelocity().y });

    }//glm::vec2 interupted = earliestMove * (1 - earliestTime);
    //intersection = NewPosition - (2.0f * interupted);
#if _DEBUG && DEBUG_WRITING
    std::cout << "Collision occured now" << std::endl;
    std::cout << "Moving to " << intersection.x << ", " << intersection.y << std::endl;
#endif

    rect1->GetParent()->GetComponent<Transform>()->SetPosition(intersection);
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
