#include "Scene.h"
#include "Stream.h"
#include "EntitySystem.h"
#include "Transform.h"
#ifdef EDITOR
#include "Container.h"
#endif


#ifdef EDITOR
void Scene::Write(std::ofstream* s) 
{
  *s << "<Scene>\n" << "<Name>\n" << name() << "\n<Entities>\n";
  
  for (auto& e : entities) 
  {
    if (e->isPrefabRoot() || e->isPrefabChild())
      continue;
    *s << e->getProto() << "\n";
    *s << "<Position>\n";
    *s << e->GetComponent<Transform>()->StartingPosition() << "\n";
  }
  *s << "</Entities>\n <Prefabs>\n";
  for (auto& p : prefabs) 
  {
    *s << p->getProto() << "\n";
  }
  *s << "</Prefabs>\n";

}

#endif

void Scene::ReadFile(const char* c)
  {
    Stream s(c);
    std::string token;
    ReadSection rs = Default;
    Entity* active = nullptr;
    while (true)
    {
      token = s.ReadString();
      if (rs == Default)
      {
        if (token == "<Name>")
          name(s.ReadString());
        else if (token == "<Entities>")
          rs = Entities;
        else if (token == "<Prefabs>")
          rs = Prefabs;
        else if (token == "")
          break;
      }
      else if (rs == Entities)
      {
        if (token == "</Entities>")
        {
          rs = Default;
        }
        else if (token == "<Position>")
          active->GetComponent<Transform>()->SetPosition(s.ReadVector());
        else 
        {
          active = EntitySystem::GetActive().CreateEntity(token.c_str());
#ifdef EDITOR
          entities.push_back(active);
#endif
        }
      }
      else if (rs == Prefabs) 
      {
        if (token == "</Prefabs>")
        {
          rs = Default;
        }
        else 
        {
          active = EntitySystem::GetActive().CreatePrefab(token.c_str());
#ifdef EDITOR
          prefabs.push_back(active);

#endif
        
        }
        }
    }
  }