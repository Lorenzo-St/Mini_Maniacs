#include "Sprite.h"
#include "Stream.h"
void Sprite::Read(Stream* s) 
{
  // <Sprite>
  //  <Texture>
  //   lol.png
  // </Sprite>
  while (true) 
  {
    std::string token = s->ReadString();
    if (token == "<Texture>")
    {
      token = s->ReadString();
      t = Textures.LoadTexture("Assets/" + token);
    }
    else if (token == "</Sprite>")
      break;
  }
}

