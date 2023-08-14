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
  void Init() 
  {
    Random<float> r;
  }

  void Read() 
  {
    ReadFile("./Managed/Scenes/Temp.scn");
  }

  void Update()
  {


  }
  void Exit() 
  {
    EntitySystem::GetActive().DestroyAll();
  }
private:

};