#include "EntitySystem.h"
#include "Entity.h"
#include "Stream.h"
#include "Physics.h"
typedef struct ESorter
{
  bool operator()(Entity* lhs, Entity* rhs) 
  {
    return lhs->GetComponent<Physics>() != nullptr;
  }

}ESorter;
void EntitySystem::Init(void) 
{
  prototypes.add(new Entity());
  prototypes.destroyAll();
}

void EntitySystem::Update(void) 
{
  activeScene.Update();
  activeScene.DoCollisions();
}

void EntitySystem::Render(void) 
{
  activeScene.Render();

}

void EntitySystem::Exit(void) 
{
  activeScene.destroyAll();
}

void EntitySystem::AddEntity(Entity* e)
{
  activeScene.add(e);
  std::sort(activeScene.GetCollection().begin(), activeScene.GetCollection().end(), ESorter());
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
  Entity* archi = prototypes.FindProto(archetypeName);
  if (archi == nullptr)
  {
    std::string path = "./Managed/" + std::string(archetypeName) + ".dat";
    Stream s = Stream(path.c_str());
    std::string token = s.ReadString();
    if (token != "<Entity>")
      return nullptr;

    archi = new Entity();
    archi->setProto(archetypeName);
    archi->Read(&s);
    prototypes.add(archi);
  }

  Entity* e = archi->Clone();
  AddEntity(e);
  e->Awake();
  e->Init();
  return e;
}

void EntitySystem::DestroyAll(void) 
{
  activeScene.destroyAll();
}