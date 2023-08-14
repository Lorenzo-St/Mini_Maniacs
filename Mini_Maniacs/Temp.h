#pragma once

#include "Scene.h"
#include "Backend.h"
#include "RNG.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "Transform.h"
#include "Physics.h"
#include "EllipCollider.h"
#include "RectCollider.h"
#include "MeshComp.h"
#include "Stream.h"
class TempScene : public Scene
{
public:
  Entity* e;
  Entity* e2;

  Entity* floor;
  void Init() 
  {
    e = EntitySystem::GetActive().CreateEntity("St");
    floor = new Entity();
    floor->Tag(Ground);
    floor->AddComponent(new RectCollider());
    floor->AddComponent(new Transform());
    floor->GetComponent<Transform>()->SetPosition({ 0, -100 });
    floor->GetComponent<Transform>()->SetScale({ 1000, .01f });
    floor->GetComponent<RectCollider>()->addLine({  500,  0 },  { -500,  0 });

    EntitySystem::GetActive().AddEntity(floor);

    Random<float> r;
  }

  void Read() 
  {
    Stream s("./Managed/Scenes/Temp.scn");

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
          rs = Default;
        EntitySystem::GetActive().CreateEntity(token.c_str());
      }
    }

  }

  void Update()
  {
    api.SetColor({ 0,0,0,255 });
    api.DrawRect({ 0,-5 }, { 1000, 10 });


  }
  void Exit() 
  {
    EntitySystem::GetActive().DestroyAll();
  }
private:

};