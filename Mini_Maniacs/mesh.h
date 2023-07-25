#pragma once
#include <vector>
#include <stdexcept>
#include "SDL.h"
#include "Object.hpp"
#include "Render API.h"

class RenderFront;

class mesh : Object
{
public:
  friend mesh* RenderFront::CreateMesh(void);
  mesh* Clone(void) 
  {
    return new mesh(*this);
  } 

  void AddVertex(SDL_FPoint position, SDL_Color  color, SDL_FPoint tex_coord);
  void AddVertex(SDL_FPoint const* position, SDL_Color const* color, SDL_FPoint const* tex_coord);

  void Draw(void);
  void Destroy(void) { delete this; }
  mesh() {  };
  mesh(mesh const& m) { verticies = std::vector<SDL_Vertex>(m.verticies); }
private:

  std::vector<SDL_Vertex> verticies;
  static inline RenderFront const& Renderer = api;
};


// Build out Mesh system and renderer. Get things rendering then start building out SIMPLE. And I mean a SIMPLE, SIMPLE fucking S. I. M. P. L. E
// Simple System based Engine. Then Build Game on top of that
