#include "MeshComp.h"
#include "Stream.h"

void Mesh::AddVertex(SDL_FPoint* pos, SDL_Color* color, SDL_FPoint* UV) 
{
  if(m)
    const_cast<mesh*>(m)->AddVertex(pos, color, UV);

}

void Mesh::Read(Stream* s) 
{
  // In file order, 
// <Sprite>
//   <Count>
//     6
//   <Points>
//     1.0 [X
//     2.5 [Y 
//     255 [R
//     255 [G
//     255 [B
//     255 [A
//     0.0 [U
//     1.0 [V
//   This however many times there are points
// 
// <Next Component>
  m = new mesh();
  std::string token = s->ReadString();
  if (token != "<Count>")
    throw std::runtime_error("Mesh doesn't have point count");
  int count = s->ReadInt();
  token = s->ReadString();
  if(token != "<Points>")
    throw std::runtime_error("Mesh doesn't have point section");
  for (auto i = 0; i < count; ++i) 
  {
    SDL_FPoint f = s->ReadFPoint();
    SDL_Color c = s->ReadColor();
    SDL_FPoint u = s->ReadFPoint();
    const_cast<mesh*>(m)->AddVertex(&f, &c, &u);
    
  }
  token = s->ReadString();
  if (token == "</Mesh>")
    return;


};

