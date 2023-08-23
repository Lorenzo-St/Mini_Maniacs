#include "Collider.h"
#include "Stream.h"

void Collider::Read(Stream* s)
{
  std::string token;
  while (true) 
  {
    token = s->ReadString();
    if (token == "<isTrigger>")
      isTrigger = s->ReadBool();
    else if (token == "</Collider>")
      return;
  }

};

void Collider::Write(std::ofstream* s) 
{
  *s << "<Collider>\n";
  *s << "<isTrigger>\n";
  *s << isTrigger << "\n";
  *s << "</Collider>\n";
}
