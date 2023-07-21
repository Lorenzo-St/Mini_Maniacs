#include <iostream>
#include <string>
#include "SDL.h"
#include "Backend.h"
#include "Engine.h"

int main(int argc, char* argv[])
{
  Engine engine;
  engine.Init();
  Input.addBinding(Enter, { SDLK_g });
  

  engine.Update();
  


  

  return 0;
}