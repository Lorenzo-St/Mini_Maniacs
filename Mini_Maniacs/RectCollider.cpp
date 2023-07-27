#include "RectCollider.h"
#include "Stream.h"

void RectCollider::Read(Stream* s)
{ 
  // <RectCollider>
  //  <Width>
  //   10.0
  //  <Height>
  //   20.0
  // </RectCollider>
  // 
  while (true) 
  {
    std::string token = s->ReadString();
  
    if (token == "<Width>")
      width = s->ReadFloat();
    else if (token == "<Height>")
      height = s->ReadFloat();
    else if (token == "</RectCollider>")
      break;
  }
  

};