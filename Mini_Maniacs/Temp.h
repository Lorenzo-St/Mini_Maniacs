#pragma once

#include "Scene.h"
#include "Backend.h"
#include "RNG.h"



class TempScene : public Scene
{
public:
  Mesh* m;
  void Init() 
  {
    m = api.CreateMesh();
    m->AddVertex({ -.5f, -.5f }, { 255,   0, 255, 255 }, { 0, 1 });
    m->AddVertex({ -.5f,  .5f }, {   0, 255, 255, 255 }, { 0, 0 });
    m->AddVertex({  .5f,  .5f }, { 255, 255, 255, 255 }, { 1, 0 });
    m->AddVertex({  .5f,  .5f }, { 255, 255, 255, 255 }, { 1, 0 });
    m->AddVertex({  .5f, -.5f }, {   0,   0, 255, 255 }, { 1, 1 });
    m->AddVertex({ -.5f, -.5f }, { 255,   0, 255, 255 }, { 0, 1 });
    updates = 0;
    Random<float> r;
    api.SetMatrixData({ r.Next(-200.f, 200.f), r.Next(-200.f, 200.f) }, {100, 100}, 0);
    std::cout << r.Next() << std::endl;
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
    m->Destroy();
    m = nullptr;
    ++restarts;
  }
private:

  int updates;
  int restarts;
};