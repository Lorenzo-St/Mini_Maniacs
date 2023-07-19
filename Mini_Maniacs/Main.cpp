#include "SDL.h"
#include <iostream>
#include "Render API.h"
#include "mesh.h"
#include "Time.h"
#include "../GLM/ext/matrix_transform.hpp"
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
  glm::vec2 pos = { 0,0 };
  glm::vec2 scale(300, 250);
  float rot = 0;
  front.SetMatrixData(pos, scale, rot);
  while (running)
  {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
      running = false;
    }
    front.Update();
    front.SetMatrixData(pos, scale, rot);
    front.Draw(verticies);
    pos.x += 10;
    if (pos.x >= front.GetWindowWidth() / 2.0f)
      pos.x = -front.GetWindowWidth() / 2.0f;
    rot += .1;
#if 0
    std::cout << "FR: " << 1.0f/Time.deltaTime() << " DT: " << Time.deltaTime() << std::endl;
#endif


  }

  return 0;
}