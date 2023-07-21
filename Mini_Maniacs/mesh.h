#pragma once
#include "SDL.h"
#include <vector>
#include "Object.hpp"
#include "Render API.h"

class RenderFront;

class Mesh : Object
{
public:
  friend Mesh* RenderFront::CreateMesh(void);
  Mesh* Clone(void) 
  {
    return new Mesh(*this);
  } 

  void AddVertex(SDL_FPoint position, SDL_Color  color, SDL_FPoint tex_coord);
  void Draw(void);
  void Destroy(void) { delete this; }
private:
  Mesh(RenderFront const* front) { Renderer = front; }
  Mesh(Mesh const& m) { Renderer = m.Renderer; verticies = std::vector<SDL_Vertex>(m.verticies); }

  std::vector<SDL_Vertex> verticies;
  const RenderFront* Renderer;
};


// Build out Mesh system and renderer. Get things rendering then start building out SIMPLE. And I mean a SIMPLE, SIMPLE fucking S. I. M. P. L. E
// Simple System based Engine. Then Build Game on top of that
