#include <iostream>
#include <string>
#include "SDL.h"
#include "Backend.h"
#include "Engine.h"
#include "SceneSystem.h"
int main(int argc, char* argv[])
{
  Engine engine;
  engine.addSystem(new SceneSystem());
  engine.Init();
  Input.addBinding(Enter, { SDLK_g });
  

  engine.Update();
  


  

  return 0;
}