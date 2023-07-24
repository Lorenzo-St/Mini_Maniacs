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

Entity* EntityContainer::Find(const char* name) 
{
  for (auto& e : entities) 
  {
    if (e->isNamed(std::string(name)))
      return e;
  }
  return nullptr;
}


EntityContainer::~EntityContainer() 
{ 
  for (auto& e : entities) 
  { 
    delete e; 
  } 
}
