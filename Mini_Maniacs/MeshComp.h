#pragma once
#include "Component.h"
#include "mesh.h"
#include "glm.hpp"
class Mesh : public Component
{
public:
  Mesh() = default;
  Mesh(Mesh const* ml) : m(ml->m), matrix(ml->matrix) {  }
  Mesh* Clone() { return new Mesh(this); };
  void Read(Stream* s);
  void Write(std::ofstream* s);

  void Render(void);
  
  void SetMesh(mesh* me) { m = me; };
  void CreateMesh(void) { m = new mesh(); }
  void AddVertex(SDL_FPoint* pos, SDL_Color* color, SDL_FPoint* UV);

  void SetMatrix(glm::mat4x4 const& a) { matrix = a; }

private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------

  const mesh* m = nullptr;
  glm::mat4x4 matrix = glm::mat4x4(1.0f);

};



