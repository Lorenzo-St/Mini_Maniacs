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
  Entity* e;
  void Init() 
  {
    e = EntitySystem::GetActive().CreateEntity("Entity");


    updates = 0;
    Random<float> r;
    api.SetMatrixData({ r.Next(-200.f, 200.f), r.Next(-200.f, 200.f) }, {100, 100}, 0);
  }
  void Update()
  {
    ++updates;
    if (updates >= 400)
      getSceneSystem()->SetNextScene(this);
  }
  void Exit() 
  {
    ++restarts;
    EntitySystem::GetActive().DestroyAll();
  }
private:

  int updates;
  int restarts;
};