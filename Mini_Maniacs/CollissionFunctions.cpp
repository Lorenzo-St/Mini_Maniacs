#include <iostream>
#include "RectCollider.h"
#include "Collider.h"
#include "CollisionFunctions.h"
#include "Entity.h"
#include "Transform.h"
#define DRAW_DEBUG_LINES 1
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
  glm::vec2 OldPosition = rect1->GetParent()->GetComponent<Transform>()->GetOldPosition();
  glm::vec2 NewPosition = rect1->GetParent()->GetComponent<Transform>()->GetPosition();

  RectCollider* mover = static_cast<RectCollider*>(rect1);
  RectCollider* wall = static_cast<RectCollider*>(rect2);
  float earliestTime = 2;

  // Check line collision along the movement for each point, if there is any collision then the rects collided
  for (auto& l : mover->getSegments()) 
  {
    glm::vec2 startpos = OldPosition + l[0];
    glm::vec2 endpos = NewPosition + l[0];
    glm::vec2 moveVec = endpos - startpos;
    for (auto& segment : wall->getSegments()) 
    {
      glm::vec2 wallVec = segment[1] - segment[0];
      glm::vec2 wallNorm = { wallVec.y, -wallVec.x };
      wallNorm = glm::normalize(wallNorm);
      if (glm::dot(moveVec, wallNorm) == 0)
        continue;
      if (glm::dot(wallNorm, startpos) <= glm::dot(wallNorm, segment[0]) && glm::dot(wallNorm, endpos) < glm::dot(wallNorm, segment[1]))
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
      if (ti < earliestTime)
        earliestTime = ti;
    }    
  }
#if _DEBUG && DRAW_DEBUG_LINES
  glm::vec2 scale = rect1->GetParent()->GetComponent<Transform>()->GetVelocity();
  glm::vec2 posi = (OldPosition + (scale/2.0f));
  scale = glm::abs(scale);
  if (earliestTime < 1)
    scale *= earliestTime;
  if (scale.x = 0)
    scale.x = 10;
  if (scale.y = 0)
    scale.y = 10;
  
  api.DrawRect(posi, scale);
#endif 
  if (earliestTime < 1) 
  {
    glm::vec2 moveVec = NewPosition - OldPosition;
    glm::vec2 intersection = OldPosition + (moveVec * earliestTime);
    std::cout << "Collision occured now" << std::endl;
    std::cout << "Moving to " << intersection.x << ", " << intersection.y << std::endl;
    rect1->GetParent()->GetComponent<Transform>()->SetPosition(intersection);
    rect1->GetParent()->GetComponent<Transform>()->SetAcceleration({0,0});

  }
  
  

}

void CircleCollision(Collider* Ellip1, Collider* Ellip2) 
{

}

void RectEllipCollision(Collider* rect1, Collider* Ellips2) 
{

}
