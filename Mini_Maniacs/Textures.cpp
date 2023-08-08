#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Textures.h"
#include "SDL.h"

TextureManager Textures;

void TextureManager::SetRenderer(SDL_Renderer* r)
{ 
  renderer = r; 
}


Texture* TextureManager::LoadTexture(std::string const& filename)
{
  for (auto& t : textures) 
  {
    if (t->name() == filename)
      return t;
  }
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
  SDL_UpdateTexture(texture, &tex, file, w * channels);

  SDL_SetTextureScaleMode(texture, textureScalingForLoad);
  Texture* t = new Texture(texture, w, h);
  t->name(filename);
  textures.push_back(t);
  stbi_image_free(file);
  return t;

}

Texture* TextureManager::LoadTexture(const char* filename)
{
  std::string s = std::string(filename);
  return LoadTexture(s);
}

void TextureManager::DropTexture(Texture* ti)
{
  int i = 0;
  for (auto& t : textures) 
  {
    if (t->name() == ti->name())
    {
      delete t;
      textures.erase(textures.begin() + i);
    }
    ++i;
  }
}

void TextureManager::SetScalingMode(SDL_ScaleMode s) 
{
  textureScalingForLoad = s;
}

void TextureManager::DropAll(void) 
{
  for (auto& texture : textures) 
  {
    SDL_DestroyTexture(texture->texture());
    delete texture;
  }
  textures.clear();
}



