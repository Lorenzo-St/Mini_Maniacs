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
  glm::mat4x4 mat = glm::identity<glm::mat4x4>();
  mat = glm::translate(mat, { 100, 0, 0 });
  mat = glm::scale(mat, { 200, 300, 0 });
  mat = glm::rotate(mat, 0.f, { 0,0,1 });
  front.SetMatrix(mat);
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