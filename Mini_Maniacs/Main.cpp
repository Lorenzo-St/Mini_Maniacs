#include "SDL.h"
#include <iostream>
#include "Render API.h"
#include "mesh.h"
#include "Time.h"
SDL_Vertex verticies[] =
{
  {{ 0.0f, 1.0f},{255,0,0,255},{0.0f,0.0f}},
  {{ 0.5f, 0.0f},{0,255,0,255},{0.5f,1.0f}},
  {{ 1.0f, 1.0f},{0,0,255,255},{1.0f,0.0f}}
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
  while (running)
  {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
      running = false;
    }
    front.Update();
    SDL_Rect reky = { .5f, .25f, .5f, .5f };
    int test = SDL_RenderGeometry(front.GetRenderer(), nullptr, verticies, 3, nullptr, 3);
#if 0
    std::cout << test << std::endl;
#endif

    SDL_RenderFillRect(front.GetRenderer(), &reky);

  }

  return 0;
}