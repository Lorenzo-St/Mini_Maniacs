#include "EntitySystem.h"
#include "Entity.h"

void EntitySystem::Init(void) 
{
  prototypes.add(new Entity(this));
  prototypes.destroyAll();
}

void EntitySystem::Update(void) 
{

}

void EntitySystem::Render(void) 
{

}

void EntitySystem::Exit(void) 
{
  activeScene.destroyAll();
}

void EntitySystem::AddEntity(Entity* e)
{
  activeScene.add(e);
}
//void EntitySystem::AddEntity(Entity* e) const
//{
//  activeScene.add(e);
//}


Entity* EntitySystem::CloneEntity(Entity* e) 
{
  Entity* el = e->Clone();
  activeScene.add(el);
  return el;
}


Entity* EntitySystem::CreateEntity(const char* archetypeName) 
{


  return nullptr;
}

void EntitySystem::DestroyAll(void) 
{

}