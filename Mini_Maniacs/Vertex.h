#pragma once
#include "glm.hpp"
#include "SDL.h"



typedef struct Vertex
{
  union
  {
    SDL_FPoint position;
    glm::vec2 pos;
  };
  SDL_Color color;
  SDL_FPoint tex_coord;
}Vertex;
