#include "Entity.h"
#include "Component.h"
#include "Stream.h"
#include "Transform.h"

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
  name = e->name;

  for (auto& c : e->components)
    components.push_back(c->Clone());
}

void Entity::Read(Stream* s) 
{
  while (true)
  {
    Component* c = nullptr;
    std::string token = s->ReadString();
    if (token == "")
      break;
    else if (token == "<Name>")
      name = s->ReadString();
    else if (token == "<Transform>")
    {
      c = new Transform();
    }
    if (c) 
    {
      c->Read(s);
      AddComponent(c);
    }
    


  }

}



