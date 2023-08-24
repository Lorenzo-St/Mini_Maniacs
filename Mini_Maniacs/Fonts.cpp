#include "Fonts.h"

FontInfo* Fonts::LoadFont(const char* c)
{
  return LoadFont(c, 24);
}

FontInfo* Fonts::LoadFont(const char* c, int size)
{
  if (instance == nullptr)
    instance = new Fonts();
  FontInfo* f = new FontInfo();
  f->font = TTF_OpenFont(c, size);
  f->name = c;
  instance->fonts.push_back(f);
  return instance->fonts[instance->fonts.size() - 1];
}

FontInfo* Fonts::FetchFont(const char* name) 
{
  if (instance == nullptr)
  {
    instance = new Fonts();
    return nullptr;
  }
  for (auto const& c : instance->fonts) 
  {
    if (c->name == name)
      return c;
  }
  return nullptr;
}

void Fonts::DeleteFonts() 
{
  if (instance == nullptr)
  {
    instance = new Fonts();
    return;
  }
  for (auto& f : instance->fonts) 
  {
    TTF_CloseFont(f->font);
    f->font = nullptr;
    delete f;
    f = nullptr;
  }

}
