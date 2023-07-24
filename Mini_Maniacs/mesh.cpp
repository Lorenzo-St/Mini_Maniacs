#include "mesh.h"
#include "Render API.h"
void mesh::AddVertex(SDL_FPoint position, SDL_Color  color, SDL_FPoint tex_coord) 
{
  verticies.push_back({ position, color, tex_coord });
}

void mesh::Draw(void) 
{
  Renderer.Draw(verticies);
}