#pragma once
#include "SDL.h"
#include "glm.hpp"
#include <vector>
#include "Time.h"
#include "Vertex.h"
typedef long RendErr;

class RenderFront 
{
public:
  struct Camera 
  {
    SDL_FPoint pos;
  };


  RendErr GetError(void);
  void Init(void);
  void Shutdown(void);
  void Update(void);


  void Draw(std::vector<SDL_Vertex> const& mesh) const;
  void SetMatrix(glm::mat4x4 const& matrix);
  void SetMatrixData(glm::vec2 pos, glm::vec2 scale, float rotation);

  int GetWindowWidth(void) { return Width; }
  int GetWindowHeight(void) { return Height; }

#ifdef _DEBUG
  SDL_Renderer* GetRenderer(void) { return renderer; };
  SDL_Window* GetWindow(void) { return window; };
#endif
private:
  
  int Width = 1280;
  int Height = 720;
  int TargetFrameRate = 60;
  float frameRateMillis = 0;
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Rect ViewPort;
  glm::mat4x4 renderMatrix = glm::mat4x4(1.0f);
};