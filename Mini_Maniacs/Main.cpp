#include "SDL.h"
#include "EventProcessing.h"
#include <iostream>
#include "Render API.h"
#include "mesh.h"
#include "Time.h"
#include "../GLM/ext/matrix_transform.hpp"
std::vector<SDL_Vertex> verticies =
{
  {{-0.5f,-0.5f},{255,0,0,255},{0.0f,0.0f}},
  {{ 0.0f, 0.5f},{255,0,122,255},{0.5f,1.0f}},
  {{ 0.5f,-0.5f},{0,0,255,255},{1.0f,0.0f}}
};


int main(int argc, char* argv[])
{
  api.Init();
  if (api.GetError() != 0)
  {
    api.Shutdown();
    return -1;
  }
  SDL_Event event;
  bool running = true;
  glm::vec2 pos = { 0,0 };
  glm::vec2 scale(50, 50);
  float rot = 0;
  api.SetMatrixData(pos, scale, rot);
  while (running)
  {

    api.Update();
    api.SetMatrixData(pos, scale, rot);
    api.Draw(verticies);
    pos.x += 50 * Time.deltaTime();
    if (pos.x >= api.GetWindowWidth() / 3.0f)
      pos.x = -(api.GetWindowWidth() / 3.0f);
#if 0
    std::cout << "FR: " << 1.0/Time.deltaTime() << " DT: " << Time.deltaTime() << std::endl;
#endif
    while (SDL_PollEvent(&event)) 
    {
      if (event.type == SDL_QUIT || event.type == SDL_APP_TERMINATING)
      {
        running = false;
      }
      else 
      {
        ProcessEvent(event);
      }

    }
  }

  return 0;
}