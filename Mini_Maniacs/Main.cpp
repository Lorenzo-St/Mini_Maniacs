#include "SDL.h"
#include <iostream>
#include "Render API.h"
#include "mesh.h"
#include "Time.h"
std::vector<SDL_Vertex> verticies =
{
  {{ 0.0f, 1.0f},{255,0,0,255},{0.0f,0.0f}},
  {{ 0.5f, 0.0f},{0,255,0,255},{0.5f,1.0f}},
  {{ 1.0f, 1.0f},{0,0,255,255},{1.0f,0.0f}}
};

typedef union temp 
{
  glm::vec2 pos;
  SDL_FPoint position;
};

int main(int argc, char* argv[])
{
  RenderFront front;
  front.Init();
  temp lol;
  lol.pos = { 1, 1 };
  std::cout << lol.pos.x << ", " << lol.pos.y << std::endl;
  std::cout << lol.position.x << ", " << lol.position.y << std::endl;

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
    SDL_Rect reky = { 100, 100, 100, 100 };
    front.Draw(verticies);
#if 0
    std::cout << "FR: " << 1.0f/Time.deltaTime() << " DT: " << Time.deltaTime() << std::endl;
#endif

    SDL_RenderFillRect(front.GetRenderer(), &reky);

  }

  return 0;
}