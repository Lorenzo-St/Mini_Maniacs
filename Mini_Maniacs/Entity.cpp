#include "Entity.h"
#include "Component.h"

void Entity::Awake(void) 
{
  for (auto& comp : components)
    comp->Awake();
}

void Entity::Init(void) 
{
  for (auto& comp : components)
    comp->Init();
}

void Entity::Update(void) 
{
  for (auto& comp : components)
    comp->Update();
}

void Entity::Render(void) 
{
  for (auto& comp : components)
    comp->Render();
}

void Entity::Exit(void) 
{
  for (auto& comp : components)
    comp->Exit();
}

void Entity::SetActive(bool b)
{
  Object::SetActive(b);
  if (isActive())
  {
    for (auto& c : components)
    {
      c->Awake();
    }
  }
};

Entity::Entity(Entity const* e)
{ 
  for (auto& c : e->components)
    components.push_back(c->Clone());
}



