#pragma once

#include "Scene.h"
#include "Backend.h"
#include "RNG.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "Transform.h"
class TempScene : public Scene
{
public:
  mesh* m;
  
  Entity* e;
  void Init() 
  {
    e = EntitySystem::GetActive().CreateEntity("Entity");

    m = api.CreateMesh();
    m->AddVertex({ -.5f, -.5f }, { 255,   0, 255, 255 }, { 0, 1 });
    m->AddVertex({ -.5f,  .5f }, {   0, 255, 255, 255 }, { 0, 0 });
    m->AddVertex({  .5f,  .5f }, { 255, 255, 255, 255 }, { 1, 0 });
    m->AddVertex({  .5f,  .5f }, { 255, 255, 255, 255 }, { 1, 0 });
    m->AddVertex({  .5f, -.5f }, { 255, 255,   0, 255 }, { 1, 1 });
    m->AddVertex({ -.5f, -.5f }, { 255,   0, 255, 255 }, { 0, 1 });
    updates = 0;
    Random<float> r;
    api.SetMatrixData({ r.Next(-200.f, 200.f), r.Next(-200.f, 200.f) }, {100, 100}, 0);
  }
  void Update()
  {
    ++updates;
    if (updates >= 400)
      getSceneSystem()->SetNextScene(this);
    api.SetMatrixData({ 0,0 }, { 100,100 }, 0);
    m->Draw();
  }
  void Exit() 
  {
    m->Destroy();
    m = nullptr;
    ++restarts;
    EntitySystem::GetActive().DestroyAll();
  }
private:

  int updates;
  int restarts;
};