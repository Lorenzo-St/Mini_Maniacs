#include "RectCollider.h"
#include "Collider.h"
#include "CollisionFunctions.h"
#include "Entity.h"
#include "Transform.h"

typedef struct line 
{
  glm::vec2 point1;
  glm::vec2 point2;
}line;

void RectangleCollision(Collider* rect1, Collider* rect2) 
{
  RectCollider* rec1 = static_cast<RectCollider*>(rect1);
  RectCollider* rec2 = static_cast<RectCollider*>(rect2);
  glm::vec2 rect1Pos = rec1->GetParent()->GetComponent<Transform>()->GetPosition();
  glm::vec2 rect2Pos = rec2->GetParent()->GetComponent<Transform>()->GetPosition();

}

void CircleCollision(Collider* Ellip1, Collider* Ellip2) 
{

}

void RectEllipCollision(Collider* rect1, Collider* Ellips2) 
{

}
