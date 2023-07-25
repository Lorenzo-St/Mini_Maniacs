#include "mesh.h"
#include "Render API.h"
void mesh::AddVertex(SDL_FPoint position, SDL_Color  color, SDL_FPoint tex_coord) 
{
  verticies.push_back({ position, color, tex_coord });
}

void mesh::AddVertex(SDL_FPoint const* position, SDL_Color const* color, SDL_FPoint const* tex_coord)
{ 
  verticies.push_back({ *position, *color, *tex_coord });
}

void mesh::Draw(void) const
{
  Renderer.Draw(verticies);
}

void mesh::Draw(void)
{
  Renderer.Draw(verticies);
}