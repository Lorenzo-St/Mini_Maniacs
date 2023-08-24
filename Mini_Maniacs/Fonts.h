#pragma once
#include "SDL_ttf.h"
#include <string>
#include <vector>
typedef struct FontInfo 
{
  TTF_Font* font;
  const char* name;
}FontInfo;

class Fonts 
{
public:
  static FontInfo* LoadFont(const char* c);
  static FontInfo* LoadFont(const char* c, int fontsize);

  static FontInfo* FetchFont(const char* name);
  static void DeleteFonts();


private:
  Fonts() = default;
  std::vector<FontInfo*> fonts;
  static inline Fonts* instance;

};