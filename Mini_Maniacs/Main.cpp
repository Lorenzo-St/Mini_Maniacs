#include <iostream>
#include <string>
#define Editor 0 
#include "SDL.h"
#include "Backend.h"
#include "Engine.h"
#include "SceneSystem.h"
#include "CollisionLedger.h"
#include "EntitySystem.h"
#if Editor
#include "EditorSystem.h"
#endif
int main(int argc, char* argv[])
{
  Engine engine;
#if Editor
  engine.addSystem(new  EditorSystem());

#endif
  engine.addSystem(new SceneSystem());
  engine.addSystem(new EntitySystem());
  engine.addSystem(CollisionLedger::GetInstance());
  api.setZoom(3.f);
  api.setClearColor({ 0,0,0,255 });
  engine.Init();
  InputSystem::addBinding(Jump, { SDLK_SPACE });
  InputSystem::addBinding(PosX, { SDLK_d });
  InputSystem::addBinding(NegX, { SDLK_a });


  engine.Update();
  


  

  return 0;
}