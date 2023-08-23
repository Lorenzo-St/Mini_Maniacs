#pragma once
#include "SDL.h"
#include <string>
#include <vector>
typedef struct Texture 
{
public:
  Texture(SDL_Texture* te, int wi, int he):t(te), w(wi), h(he) {}
  SDL_Texture* const texture() 
  {
    return t;
  }
  std::string const& name() const 
  {
    return n;
  }
  void name(std::string const& s) 
  {
    n = s;
  }
  int Width() const
  {
    return w;
  }
  int Height() const
  {
    return h;
  }
private:
  std::string n;
  SDL_Texture* t;
  int w, h;
}Texture;

class TextureManager
{
public:
  Texture* LoadTexture(std::string const& filename);
  Texture* LoadTexture(const char* filename);

  void DropTexture(Texture* t);
  void DropAll(void);

  

  void SetRenderer(SDL_Renderer* r);
  void SetScalingMode(SDL_ScaleMode s);
private:
  std::vector<Texture*> textures;
  SDL_Renderer* renderer = nullptr;
  SDL_ScaleMode textureScalingForLoad = SDL_ScaleModeNearest;

};

extern TextureManager Textures;
