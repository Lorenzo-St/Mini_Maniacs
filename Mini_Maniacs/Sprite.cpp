#include "Sprite.h"
#include "Stream.h"
#include "Textures.h"
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

void Sprite::Write(std::ostream* s) 
{
  *s << "<Sprite>\n";
  *s << "<Texture>\n";
  *s << t->name() << "\n";
  *s << "</Sprite>\n";
}


