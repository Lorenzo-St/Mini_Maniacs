#include "SDL.h"
#include <iostream>

SDL_Vertex verticies[] =
{
  {{ 0.0f, 1.0f},{255,0,0,255},{0.0f,0.0f}},
  {{ 0.5f, 0.0f},{0,255,0,255},{0.5f,1.0f}},
  {{ 1.0f, 1.0f},{0,0,255,255},{1.0f,0.0f}}
};


int main(int argc, char* argv[])
{
  const int WIDTH = 1280;
  const int HEIGHT = 720;
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    std::cerr << "Initilization failed" << SDL_GetError() << std::endl;
    return -1;
  }
  
  window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, 0);
  
  SDL_Rect rect = { 0, 0, WIDTH, HEIGHT };
  SDL_RenderSetViewport(renderer, &rect);
  SDL_RenderSetScale(renderer, WIDTH, HEIGHT);
  SDL_Event event;
  while (SDL_WaitEvent(&event))
  {
    SDL_Rect reky = { .5f, .25f, .5f, .5f };
    SDL_SetRenderDrawColor(renderer, 0, 0, 255,  255);
    SDL_RenderClear(renderer);
    int test = SDL_RenderGeometry(renderer, nullptr, verticies, 3, nullptr, 3);
#if 0
    std::cout << test << std::endl;
#endif
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &reky);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}