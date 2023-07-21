#pragma once
#include "Scene.h"
class TempScene : public Scene
{
public:
  void Init() 
  {
    updates = 0;
  }
  void Update()
  {
    ++updates;
    if (updates >= 200)
      getSceneSystem()->SetNextScene(this);
  }
  void Exit() 
  {
    ++restarts;
  }
private:

  int updates;
  int restarts;
};