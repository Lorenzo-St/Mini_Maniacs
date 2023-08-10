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
class TempScene : public Scene
{
public:
  Entity* e;
  Entity* floor;
  void Init() 
  {
    e = EntitySystem::GetActive().CreateEntity("Entity");
    floor = new Entity();
    floor->Tag(Ground);
    floor->AddComponent(new RectCollider());
    floor->AddComponent(new Transform());
    floor->GetComponent<Transform>()->SetPosition({ 0, -100 });
    floor->GetComponent<Transform>()->SetScale({ 1000, .01f });
    floor->GetComponent<RectCollider>()->addLine({  500,  0 },  { -500,  0 });
    //floor->GetComponent<RectCollider>()->addLine({ -500, -5 },  {  500, -5 });
    //floor->GetComponent<RectCollider>()->addLine({ -500,  0 },  { -500, -5 });
    //floor->GetComponent<RectCollider>()->addLine({  500, -5 },  { -500,  0 });

    EntitySystem::GetActive().AddEntity(floor);


    updates = 0;
    Random<float> r;
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

  int updates;
  int restarts;
};