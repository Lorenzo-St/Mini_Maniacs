#include "Stream.h"
#include "glm.hpp"
Stream::Stream(const char* file) 
{
  fileStream.open(file);
}

Stream::~Stream(void) 
{
  if (fileStream.is_open())
    fileStream.close();
}

int Stream::ReadInt(void) 
{
  int r;
  fileStream >> r;
  return r;
}

float Stream::ReadFloat(void) 
{
  float f;
  fileStream >> f;
  return f;
}

bool Stream::ReadBool(void) 
{
  std::string s;
  fileStream >> s;
  if (s == "1" || s == "True" || s == "true" || s == "TRUE") return true;
  else return false;
}

SDL_FPoint Stream::ReadFPoint(void) 
{
  SDL_FPoint fp = {};
  fileStream >> fp.x;
  fileStream >> fp.y;
  return fp;
}

glm::vec2 Stream::ReadVector(void)
{
  glm::vec2  fp = {};
  fileStream >> fp.x;
  fileStream >> fp.y;
  return fp;
}

SDL_Color Stream::ReadColor(void) 
{
  SDL_Color c = {};
  glm::ivec4 in = {};
  fileStream >> in.r;
  fileStream >> in.g;
  fileStream >> in.b;
  fileStream >> in.a;
  c.r = in.r;
  c.g = in.g;
  c.b = in.b;
  c.a = in.a;
  return c;
}

std::string Stream::ReadString(void) 
{
  std::string s;
  fileStream >> s;
  return s;
}

