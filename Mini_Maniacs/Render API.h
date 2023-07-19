#pragma once
#include "SDL.h"
#include "glm.hpp"
#include <vector>
#include "Time.h"
typedef long RendErr;

class RenderFront 
{
public:
  
  // System functions
  RendErr GetError(void);
  void Init(void);
  void Shutdown(void);
  void Update(void);

  // Drawing function
  void Draw(std::vector<SDL_Vertex> const& mesh) const;
  void SetMatrix(glm::mat4x4 const& matrix);
  void SetMatrixData(glm::vec2 pos, glm::vec2 scale, float rotation);

  // Window Stuff
  int GetWindowWidth(void) { return Width; }
  int GetWindowHeight(void) { return Height; }

#ifdef _DEBUG
  // Debug Functions
  SDL_Renderer* GetRenderer(void) { return renderer; };
  SDL_Window* GetWindow(void) { return window; };
#endif
private:
  struct Camera 
  {
    SDL_FPoint pos;
  };
  
  int Width = 1280;
  int Height = 720;
  int TargetFrameRate = 60;
  float frameRateMillis = 0;
  Camera c = { {0,0} };
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Rect ViewPort;
  glm::mat4x4 renderMatrix = glm::mat4x4(1.0f);
};


extern RenderFront api;