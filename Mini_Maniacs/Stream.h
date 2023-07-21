#pragma once
#include <fstream>
#include <string>
#include <SDL.h>
class Stream 
{
public:
  Stream(const char* file);
  ~Stream(void);

  int ReadInt(void);
  float ReadFloat(void);
  
  SDL_FPoint ReadVector(void);
  SDL_Color ReadColor(void);
  
  std::string ReadString(void);
private:
  std::ifstream fileStream;
};