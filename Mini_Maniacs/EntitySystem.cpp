#include "EntitySystem.h"
#include "Entity.h"

void EntitySystem::Init(void) 
{

}

void EntitySystem::Update(void) 
{

}

void EntitySystem::Render(void) 
{

}

void EntitySystem::Exit(void) 
{

}

Entity* EntitySystem::CreateEntity(void) 
{
  Entity* e = new Entity(this);
  return e;
}

Entity* EntitySystem::CreateEntity(const char* file) 
{


  return nullptr;
}

void EntitySystem::DestroyAll(void) 
{

}