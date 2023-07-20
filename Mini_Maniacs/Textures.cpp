#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Textures.h"
#include "SDL.h"

Texture TextureManager::LoadTexture(std::string const& filename)
{
  int w, h, channels;

  unsigned char* file = stbi_load(filename.c_str(), &w, &h, &channels, 0);
  SDL_Texture* texture = nullptr;
  switch (channels) 
  {
  case 4:
    texture = SDL_CreateTexture(Textures.renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, w, h);
    break;
  case 3:
    texture = SDL_CreateTexture(Textures.renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, w, h);
    break;
  }
  SDL_Rect tex = {0,0,w,h};
  SDL_UpdateTexture(texture, &tex, file, w);

  SDL_SetTextureScaleMode(texture, textureScalingForLoad);
  textures.push_back(texture);
  stbi_image_free(file);
  return texture;

}

Texture TextureManager::LoadTexture(const char* filename)
{
  return nullptr;
}

void TextureManager::DropTexture(Texture t)
{

}

void TextureManager::SetScalingMode(SDL_ScaleMode s) 
{
  textureScalingForLoad = s;
}

void TextureManager::DropAll(void) 
{
  for (auto& texture : textures) 
  {
    SDL_DestroyTexture(texture);
  }
}



TextureManager Textures;