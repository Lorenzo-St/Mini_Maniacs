#include "EntitySystem.h"
#include "Entity.h"
#include "Stream.h"

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
  activeScene.add(e);
  return e;
}

void EntitySystem::DestroyAll(void) 
{
  activeScene.destroyAll();
}