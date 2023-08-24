#include <vector>
#ifdef EDITOR
#include <filesystem>
#endif

#include "EntitySystem.h"
#include "Entity.h"
#include "Stream.h"
#include "Physics.h"
#include "Transform.h"
#include "RectCollider.h"

typedef struct ESorter
{
  bool operator()(Entity const* lhs, Entity const* rhs) 
  {
    return lhs->GetComponent<Physics>() != nullptr && rhs->GetComponent<Physics>()== nullptr;
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

Container<Entity>& EntitySystem::FindAllWithTag(Tags tag)
{
  searchResult.GetCollection().clear();
  std::vector<Entity*> const& ative = activeScene.GetCollection();

  for (auto const& e : ative) 
  { 
    if (e->Tag() == tag)
      searchResult.add(e);
  }
  return searchResult;
}

void EntitySystem::Render(void) 
{
  activeScene.Render();

}

void EntitySystem::Exit(void) 
{
  activeScene.destroyAll();
  prototypes.destroyAll();
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

Entity* EntitySystem::CreatePrefab(const char* file)
{
  std::string path = "./Managed/Prefabs/" + std::string(file) + ".dat";
  Entity* prefab = new Entity();
  prefab->isPrefabRoot(true);
  Stream s = Stream(path.c_str());
  prefab->Read(&s);
  prefab->setProto(prefab->getName());
  std::string token;
  while (true)
  {
    token = s.ReadString();
    if (token == "<Entities>")
    {
      Entity* active = nullptr;
      while (token != "" || token != "</Entities>")
      {
        token = s.ReadString();
        
        if (token == "<name>")
        {
          active = CreateEntity(s.ReadString().c_str());
          active->SetParent(prefab);
          active->isPrefabChild(true);
          prefab->AddChild(active);
        }
        else if (token == "<localPosition>")
        {
          Transform* t = active->GetComponent<Transform>();
          t->SetLocalPosition(s.ReadVector());
        }
        else if (token == "<scale>") 
        {
          Transform* t = active->GetComponent<Transform>();
          t->SetScale(s.ReadVector());

        }
        else if (token == "<RectCollider>")
        {
          glm::vec2 scale = s.ReadVector();
          RectCollider* r = active->GetComponent<RectCollider>();
          r->Height(scale.y);
          r->Width(scale.x);

        }
        else if (token == "")
          break;
      }
    }
    else if (token == "")
      break;
  }
  prefab->GetComponent<Transform>()->SetPosition(prefab->GetComponent<Transform>()->GetPosition());
  activeScene.add(prefab);
  return prefab;
}



Entity* EntitySystem::CreateEntity(const char* archetypeName) 
{
  Entity* archi = prototypes.FindProto(archetypeName);
  if (archi == nullptr)
  {
    std::string path = "./Managed/Entities/" + std::string(archetypeName) + ".dat";
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

Entity* EntitySystem::FindWithName(const char* name) 
{
  return activeScene.FindName(name);
}


Entity* EntitySystem::FindWithTag(Tags tag) 
{
  std::vector<Entity*>& col = activeScene.GetCollection();
  for (auto& e : col) 
  {
    if (e->Tag() == tag)
      return e;
  }
  return nullptr;
}

#ifdef EDITOR

void EntitySystem::WritePrefab(Entity* e) 
{
  std::string path = std::filesystem::current_path().string() + ".\\Managed\\Prefabs\\" + e->getProto() + ".dat";
  std::ofstream s(path);
  e->Write(&s);
  s << "<Entities>\n ";
  for (auto e : e->GetChildren()) 
  {
    s << "<name>\n  ";
    s << e->getProto() << "\n ";
    s << "<localPosition>\n  ";
    s << e->GetComponent<Transform>()->GetLocalPosition() << "\n ";
  }

  s << "</Entities>";
}


#endif