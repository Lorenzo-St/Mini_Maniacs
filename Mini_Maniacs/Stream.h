#pragma once
#include <fstream>
#include <string>
#include <SDL.h>
#include "glm.hpp"
class Stream 
{
public:
  Stream(const char* file);
  ~Stream(void);

  int ReadInt(void);
  float ReadFloat(void);
  bool ReadBool(void);

  SDL_FPoint ReadFPoint(void);
  glm::vec2 ReadVector(void);
  SDL_Color ReadColor(void);
  
  std::string ReadString(void);
private:
  std::ifstream fileStream;
};