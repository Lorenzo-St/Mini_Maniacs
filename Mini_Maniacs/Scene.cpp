#include "Scene.h"
#include "Stream.h"
#include "EntitySystem.h"
#include "Transform.h"

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
          active = EntitySystem::GetActive().CreateEntity(token.c_str());
      }
      else if (rs == Prefabs) 
      {
        if (token == "</Prefabs>")
        {
          rs = Default;
        }
        else
          EntitySystem::GetActive().CreatePrefab(token.c_str());
      }
    }
  }