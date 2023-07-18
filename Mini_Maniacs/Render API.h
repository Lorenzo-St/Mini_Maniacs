#pragma once
#include "SDL.h"
#include <vector>
class RenderFront 
{
public:
  int GetError(void);
  void Init(void);
  void Shutdown(void);

  void Draw(std::vector<SDL_Vertex> const& mesh);

private:
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Rect ViewPort;

};