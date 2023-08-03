#include <iostream>
#include <string>
#include "SDL.h"
#include "Backend.h"
#include "Engine.h"
#include "SceneSystem.h"
#include "EntitySystem.h"
int main(int argc, char* argv[])
{
  Engine engine;
  engine.addSystem(new SceneSystem());
  engine.addSystem(new EntitySystem());
  api.setZoom(1.5f);
  engine.Init();
  Input.addBinding(Enter, { SDLK_g });
  

  engine.Update();
  


  

  return 0;
}