#pragma once
#include "SDL.h"
#include <vector>
class RenderFront;

class Mesh 
{
public:
  void AddVertex(SDL_FPoint position, SDL_Color  color, SDL_FPoint tex_coord);
private:
  std::vector<SDL_Vertex> verticies;

};


// Build out Mesh system and renderer. Get things rendering then start building out SIMPLE. And I mean a SIMPLE, SIMPLE fucking S. I. M. P. L. E
// Simple System based Engine. Then Build Game on top of that
