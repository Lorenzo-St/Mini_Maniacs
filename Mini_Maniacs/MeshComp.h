#pragma once
#include "Component.h"
#include "mesh.h"
class Mesh : public Component
{
public:
  Mesh() = default;
  Mesh(Mesh const* ml) : m(ml->m) {  }
  Mesh* Clone() { return new Mesh(this); };
  void Read(Stream* s);
  void Update(void) { if(m) m->Draw(); }
  void SetMesh(mesh* me) { m = me; };
  void CreateMesh(void) { m = new mesh(); }
  void AddVertex(SDL_FPoint* pos, SDL_Color* color, SDL_FPoint* UV);
private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------

  const mesh* m = nullptr;

};


