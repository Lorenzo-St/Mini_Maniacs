#pragma once
#include "Component.h"
#include "Textures.h"
class Sprite : public Component
{
public:
  Sprite() = default;
  Sprite(Sprite const* ml) : t(ml->t) {  }
  Sprite* Clone() { return new Sprite(this); };
  void Read(Stream* s);
  void Render(void);
  void LoadSprite(std::string s) { t = Textures.LoadTexture(s); }

private:
  // -------------------------
  // Required Component things
  // -------------------------
  constexpr bool set() { setType(__CLASS_NAME__); return true; };
  const bool s = set();
  // -------------------------

  const Texture* t = nullptr;

};
