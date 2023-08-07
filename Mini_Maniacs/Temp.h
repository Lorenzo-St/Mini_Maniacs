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
  Entity* c1;
  Entity* c2;
  void Init() 
  {
    e = EntitySystem::GetActive().CreateEntity("Entity");
    floor = new Entity();
    floor->AddComponent(new RectCollider());
    floor->AddComponent(new Transform());
    floor->GetComponent<Transform>()->SetPosition({ 0, -100 });
    floor->GetComponent<Transform>()->SetScale({ 1000, .01f });
    floor->GetComponent<RectCollider>()->addLine({  500,  0 },  { -500,  0 });
    //floor->GetComponent<RectCollider>()->addLine({ -500, -5 },  {  500, -5 });
    //floor->GetComponent<RectCollider>()->addLine({ -500,  0 },  { -500, -5 });
    //floor->GetComponent<RectCollider>()->addLine({  500, -5 },  { -500,  0 });

    EntitySystem::GetActive().AddEntity(floor);
    c1 = new Entity();
    c1->AddComponent(new EllipCollider());
    c1->AddComponent(new Transform());
    c1->AddComponent(new Physics());
    c1->GetComponent<Transform>()->SetPosition({ -100, 100 });
    c1->GetComponent<Transform>()->SetScale({ 10, 10});
    c1->GetComponent<EllipCollider>()->SetRadius(50);

    c2 = new Entity();
    c2->AddComponent(new EllipCollider());
    c2->AddComponent(new Transform());
    c2->GetComponent<Transform>()->SetPosition({ -100, 10 });
    c2->GetComponent<Transform>()->SetScale({ 10, 10 });
    c2->GetComponent<EllipCollider>()->SetRadius(50);
    EntitySystem::GetActive().AddEntity(c1);
    EntitySystem::GetActive().AddEntity(c2);

    updates = 0;
    Random<float> r;
  }
  void Update()
  {
    api.DrawRect({ 0,-5 }, { 1000, 10 });
    api.DrawEllipse(c1->GetComponent<Transform>()->GetPosition(), 50);
    api.DrawEllipse(c2->GetComponent<Transform>()->GetPosition(), 50);

  }
  void Exit() 
  {
    EntitySystem::GetActive().DestroyAll();
  }
private:

  int updates;
  int restarts;
};