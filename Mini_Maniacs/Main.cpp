#include <iostream>
#include <string>
#include "SDL.h"
#include "Backend.h"
#include "Engine.h"
#include "SceneSystem.h"
#include "CollisionLedger.h"
#include "EntitySystem.h"
#ifdef EDITOR
#include "EditorSystem.h"
#endif
int main(int argc, char* argv[])
{
  Engine engine;
#ifdef EDITOR
  engine.addSystem(new  EditorSystem());

#endif
  engine.addSystem(new SceneSystem());
  engine.addSystem(new EntitySystem());
  engine.addSystem(CollisionLedger::GetInstance());
  api.setZoom(3.f);
  api.setClearColor({ 25,25,25,255 });
  engine.Init();
  InputSystem::addBinding(Jump, { SDLK_SPACE });
  InputSystem::addBinding(PosX, { SDLK_d });
  InputSystem::addBinding(NegX, { SDLK_a });


  engine.Update();
  engine.Exit();
  return 0;
}