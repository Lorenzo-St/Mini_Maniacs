#include "Entity.h"
#include "EntityContainer.h"


void EntityContainer::destroyAll() 
{
  for (auto& e : entities)
    delete e;
}

void EntityContainer::Update() 
{
  for (auto& e : entities)
    e->Update();
}

void EntityContainer::Render() 
{
  for (auto& e : entities)
    e->Render();
}

void EntityContainer::remove(Entity* e) 
{ 
  int i = 0;
  for (auto& el : entities)
  {
    if (e == el)
      entities.erase(entities.begin() + i);
    ++i;
  }

};


EntityContainer::~EntityContainer() 
{ 
  for (auto& e : entities) 
  { 
    delete e; 
  } 
}
