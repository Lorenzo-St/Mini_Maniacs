#include "Component.h"
#include "Entity.h"
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
#include "StagePallet.h"
#include "GameManager.h"

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

bool Entity::isStatic(void) 
{ 
  return GetComponent<Physics>() == nullptr; 
}

void Entity::RemoveChild(Entity* e) 
{
  int i = 0;
  for (auto& c : Children) 
  {
    if (c == e)
    {
      c = nullptr;
      Children.erase(Children.begin() + i);
    }
    ++i;

  }
}

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
  PrefabChild = e->PrefabChild;
  PrefabRoot = e->PrefabRoot;
  SetParent(e->Parent());
  tag = e->tag;
  for (auto& c : e->components) 
  {
    Component* c2 = c->Clone();
    c2->SetParent(this);
    components.push_back(c2);

  }
}

void Entity::Write(std::ofstream* s)
{
  *s << "<Entity>\n ";
  *s << "<Name>\n  ";
  *s << name << "\n ";
  *s << "<Tag>\n  ";
  *s << toString(tag) << "\n ";
  for (auto& c : components)
    c->Write(s);
  *s << "</Entity>" <<std::endl;
}

void Entity::Read(Stream* s) 
{
  while (true)
  {
    Component* c = nullptr;
    std::string token = s->ReadString();
    if (token == "")
      break;
    else if (token == "</Entity>")
      break;
    else if (token == "<Name>")
      name = s->ReadString();
    else if (token == "<Tag>")
    {
      token = s->ReadString();
      tag = toEnum(token);
    }
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
    else if (token == "<GameManager>")
      c = new GameManager();
    else if (token == "<StagePallet>")
      c = new StagePallet();

    if (c) 
    {
      c->Read(s);
      AddComponent(c);
    }
  }

}

Container< Entity>& Entity::FindChildrenWithTag(Tags tag)
{
  static Container< Entity> result;
  result.GetCollection().clear();
  for (auto const& e : Children)
  {
    if (e->tag == tag)
      result.add(e);
  }
  return result;
}


