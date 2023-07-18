#include "SDL.h"
#include <iostream>
#include "Render API.h"

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

  SDL_Event event;
  while (SDL_WaitEvent(&event))
  {
    front.Update();
    //SDL_Rect reky = { .5f, .25f, .5f, .5f };

    //int test = SDL_RenderGeometry(renderer, nullptr, verticies, 3, nullptr, 3);
#if 0
    std::cout << test << std::endl;
#endif
    //SDL_RenderPresent(renderer);
    //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    //SDL_RenderFillRect(renderer, &reky);

  }

  return 0;
}