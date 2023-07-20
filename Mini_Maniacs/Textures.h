#pragma once
#include "SDL.h"
#include <string>
#include <vector>
#include "Render API.h"
typedef SDL_Texture* Texture;

class TextureManager 
{
public:
  Texture LoadTexture(std::string const& filename);
  Texture LoadTexture(const char* filename);

  void DropTexture(Texture t);
  void DropAll(void);

  void SetRenderer(SDL_Renderer* r) { renderer = r; };
  void SetScalingMode(SDL_ScaleMode s);
private:
  std::vector<Texture> textures;
  SDL_Renderer* renderer = nullptr;
  SDL_ScaleMode textureScalingForLoad = SDL_ScaleModeNearest;
    
};

extern TextureManager Textures;