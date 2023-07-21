#include <iostream>
#include <string>
//#include "SDL.h"
#include "Backend.h"
#include "Engine.h"

int main(int argc, char* argv[])
{
  Engine engine;
  engine.Init();
  Texture t = Textures.LoadTexture(std::string("C:\\Users\\amyst\\Pictures\\tax em.png"));

  engine.Update();
  Input.addBinding(Enter, { SDLK_g });
  


  

  return 0;
}