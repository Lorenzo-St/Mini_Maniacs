#include "SDL.h"
#include <iostream>
#include "Backend.h"
#include "../GLM/ext/matrix_transform.hpp"
std::vector<SDL_Vertex> verticies =
{
  {{-0.5f,-0.5f},{255,0,0,255},{0.0f,0.0f}},
  {{ 0.0f, 0.5f},{255,0,122,255},{0.5f,1.0f}},
  {{ 0.5f,-0.5f},{0,0,255,255},{1.0f,0.0f}}
};


int main(int argc, char* argv[])
{
  Input.addBinding(Enter, { SDLK_g });
  api.Init();
  if (api.GetError() != 0)
  {
    api.Shutdown();
    return -1;
  }
  SDL_Event event;
  bool running = true;
  glm::vec2 pos = { 0,0 };
  glm::vec2 scale(100, 100);
  float rot = 0;
  api.SetMatrixData(pos, scale, rot);
  float speed = 200;
  while (running)
  {

    api.Update();
    api.SetMatrixData(pos, scale, rot);
    api.Draw(verticies);
    pos.x += speed * Time.deltaTime();
    rot += 1 * Time.deltaTime();
    if (pos.x >= api.GetWindowWidth() / 2.0f + scale.x)
      pos.x = -(api.GetWindowWidth() / 2.0f + scale.x);
    if (Input.isPressed(Enter))
      speed += speed * Time.deltaTime();
    else if (speed > 200) 
    {
      speed *= .75f;
    }
    else if(speed < 200)
      speed = 200;
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