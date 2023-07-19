#pragma once
#include "SDL.h"
#include <vector>
#include "Vertex.h"
#include "Object.hpp"
class RenderFront;

class Mesh : Object
{
public:
  
  Mesh(RenderFront const& front) { Renderer = &front; }
  Mesh* Clone(void) 
  {
    return new Mesh(*this);
  } 

  void AddVertex(SDL_FPoint position, SDL_Color  color, SDL_FPoint tex_coord);
  void Draw(void);

private:
  Mesh(Mesh const& m) { Renderer = m.Renderer; verticies = std::vector<SDL_Vertex>(m.verticies); }

  std::vector<SDL_Vertex> verticies;
  const RenderFront* Renderer;
};


// Build out Mesh system and renderer. Get things rendering then start building out SIMPLE. And I mean a SIMPLE, SIMPLE fucking S. I. M. P. L. E
// Simple System based Engine. Then Build Game on top of that
