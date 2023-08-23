#include "mesh.h"
#include "Render API.h"
#include <iostream>
#include <fstream>

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

void mesh::Write(std::ofstream* s) const
{
  *s << "<Count>\n";
  *s << verticies.size() << "\n";
  *s << "<Points>\n";
  for (auto& a : verticies) 
  {
    *s << a.position.x << " " << a.position.y << "\n";
    *s << a.color.r << " " << a.color.g << " " << a.color.b << " " << a.color.a << "\n";
    *s << a.tex_coord.x << " " << a.tex_coord.y << "\n";
  }

}

