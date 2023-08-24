#include "Backend.h"
#include "Transform.h"
#include "Stream.h"
#include "MeshComp.h"
#include "Entity.h"
#include "Sprite.h"
void Mesh::AddVertex(SDL_FPoint* pos, SDL_Color* color, SDL_FPoint* UV) 
{
  if(m)
    const_cast<mesh*>(m)->AddVertex(pos, color, UV);

}
void Mesh::Render(void) 
{ 
  if (m) 
  {
    Sprite* s = GetParent()->GetComponent<Sprite>();
    if (s)
      api.SetTexture(s->texture());
    else 
      api.SetTexture(nullptr);

    api.SetUVMatrix(matrix);
    Transform* t = GetParent()->GetComponent<Transform>();
    api.SetMatrixData(t->GetPosition(), t->GetScale(), t->GetRotation());
    m->Draw();
    api.SetUVMatrix(glm::mat4x4(1.0f));
  }
}

void Mesh::Write(std::ofstream* s)
{
  *s << "<Mesh>\n ";
   m->Write(s);
  *s << "</Mesh>\n ";
};

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

