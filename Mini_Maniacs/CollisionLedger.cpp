#include "CollisionLedger.h"
#include "Entity.h"

void CollisionLedger::Init() 
{

}

void CollisionLedger::Update() 
{
  for (auto& i : instance->collisions)
  {
    i.e1->OnCollison(i.e2);
    i.e2->OnCollison(i.e1);
  }
  instance->collisions.clear();
}

void CollisionLedger::Exit() 
{

}
