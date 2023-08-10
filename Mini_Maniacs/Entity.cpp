#include "Entity.h"
#include "Component.h"
#include "Stream.h"
#include "Transform.h"
#include "MeshComp.h"
#include "Physics.h"
#include "RectCollider.h"
#include "EllipCollider.h"
#include "Animation.h"
#include "Sprite.h"
#include "EntitySystem.h"
#include "PlayerController.h"

Entity::Entity(void) : tag(Standard)
{ 
  es = &EntitySystem::GetActive(); 
};

Entity::Entity(Object* p) : tag(Standard)
{ 
  SetParent(p); 
  SetRoot(false); 
  const_cast<EntitySystem*>(es)->AddEntity(this); 
};

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
  protoType = e->protoType;
  for (auto& c : e->components) 
  {
    Component* c2 = c->Clone();
    c2->SetParent(this);
    components.push_back(c2);

  }
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
    else if (token == "<Tag>")
      tag = static_cast<Tags>(s->ReadInt());
    else if (token == "<Transform>")
      c = new Transform();
    else if (token == "<Mesh>")
      c = new Mesh();
    else if (token == "<RectCollider>")
      c = new RectCollider();
    else if (token == "<EllipCollider>")
      c = new EllipCollider();
    else if (token == "<Physics>")
      c = new Physics();
    else if (token == "<Sprite>")
      c = new Sprite();
    else if (token == "<Animation>")
      c = new Animation();
    else if (token == "<PlayerController>")
      c = new PlayerController();

    if (c) 
    {
      c->Read(s);
      AddComponent(c);
    }
  }

}



