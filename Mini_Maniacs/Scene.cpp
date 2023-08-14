#include "Scene.h"
#include "Stream.h"
#include "EntitySystem.h"

void Scene::ReadFile(const char* c)
  {
    Stream s(c);
    std::string token;
    ReadSection rs = Default;
    while (true)
    {
      token = s.ReadString();
      if (rs == Default)
      {
        if (token == "<Name>")
          name(s.ReadString());
        else if (token == "<Entities>")
          rs = Entities;
        else if (token == "")
          break;
      }
      else if (rs == Entities)
      {
        if (token == "</Entities>")
        {
          rs = Default;
        }
        else
          EntitySystem::GetActive().CreateEntity(token.c_str());
      }
    }
  }