#pragma once

#include "Scene.h"
#include "Backend.h"
#include "RNG.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "test.h"
class TempScene : public Scene
{
public:
  Mesh* m;
  
  Entity* e;
  void Init() 
  {
    e = new Entity();

    e->AddComponent(new Transform());
    e->AddComponent(new Sprite());
    e->AddComponent(new Animation());
    e->AddComponent(new mesh());
    e->AddComponent(new Physics());
    e->AddComponent(new Ai());
    e->AddComponent(new Door());
    m = api.CreateMesh();
    m->AddVertex({ -.5f, -.5f }, { 255,   0, 255, 255 }, { 0, 1 });
    m->AddVertex({ -.5f,  .5f }, {   0, 255, 255, 255 }, { 0, 0 });
    m->AddVertex({  .5f,  .5f }, { 255, 255, 255, 255 }, { 1, 0 });
    m->AddVertex({  .5f,  .5f }, { 255, 255, 255, 255 }, { 1, 0 });
    m->AddVertex({  .5f, -.5f }, { 255,   0,   0, 255 }, { 1, 1 });
    m->AddVertex({ -.5f, -.5f }, { 255,   0, 255, 255 }, { 0, 1 });
    updates = 0;
    Random<float> r;
    api.SetMatrixData({ r.Next(-200.f, 200.f), r.Next(-200.f, 200.f) }, {100, 100}, 0);
    Ai* a = e->GetComponent<Ai>();
  }
  void Update()
  {
    ++updates;
    if (updates >= 100)
      getSceneSystem()->SetNextScene(this);

    m->Draw();
  }
  void Exit() 
  {
    delete e;
    m->Destroy();
    m = nullptr;
    ++restarts;
  }
private:

  int updates;
  int restarts;
};