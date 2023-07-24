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
  fileStream >> c.r;
  fileStream >> c.g;
  fileStream >> c.b;
  fileStream >> c.a;
  return c;
}

std::string Stream::ReadString(void) 
{
  std::string s;
  fileStream >> s;
  return s;
}

