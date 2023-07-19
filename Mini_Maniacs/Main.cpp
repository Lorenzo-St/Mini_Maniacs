#include "SDL.h"
#include <iostream>
#include "Render API.h"
#include "mesh.h"
#include "Time.h"
std::vector<SDL_Vertex> verticies =
{
  {{-0.5f,-0.5f},{255,0,0,255},{0.0f,0.0f}},
  {{ 0.0f, 0.5f},{122,255,122,255},{0.5f,1.0f}},
  {{ 0.5f,-0.5f},{0,0,255,255},{1.0f,0.0f}}
};


int main(int argc, char* argv[])
{
  RenderFront front;
  front.Init();
  if (front.GetError() != 0) 
  {
    front.Shutdown();
    return -1;
  }
  SDL_Event event;
  bool running = true;
  front.SetTranslation( { 0, 0 } );
  front.SetScale( {10, 10 } );
  while (running)
  {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
      running = false;
    }
    front.Update();
    front.Draw(verticies);
#if 0
    std::cout << "FR: " << 1.0f/Time.deltaTime() << " DT: " << Time.deltaTime() << std::endl;
#endif


  }

  return 0;
}