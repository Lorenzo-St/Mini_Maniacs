#include <iostream>
#include <string>
#include "SDL.h"
#include "Backend.h"
#include "Engine.h"
#include "SceneSystem.h"
#include "CollisionLedger.h"
#include "EntitySystem.h"
int main(int argc, char* argv[])
{
  Engine engine;
  engine.addSystem(new SceneSystem());
  engine.addSystem(new EntitySystem());
  engine.addSystem(CollisionLedger::GetInstance());
  api.setZoom(3.f);
  engine.Init();
  InputSystem::addBinding(Jump, { SDLK_SPACE });
  InputSystem::addBinding(PosX, { SDLK_d });
  InputSystem::addBinding(NegX, { SDLK_a });


  engine.Update();
  


  

  return 0;
}