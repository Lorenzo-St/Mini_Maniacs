#pragma once

#include "Scene.h"
#include "Backend.h"




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
  }
  void Update()
  {
    ++updates;
    if (updates >= 100)
      getSceneSystem()->SetNextScene(this);

    api.SetMatrixData({ 0,0 }, { 100, 100 }, 0);
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