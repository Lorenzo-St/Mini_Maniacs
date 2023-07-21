#pragma once
#include "Scene.h"
class TempScene : public Scene 
{
public :

  void Update()
  {
    ++updates;
    if (updates >= 200)
      getSceneSystem()->SetNextScene(this);
  }

private:

  int updates;

};