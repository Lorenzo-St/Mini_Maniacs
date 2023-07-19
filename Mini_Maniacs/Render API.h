#pragma once
#include "SDL.h"
#include "glm.hpp"
#include <vector>
#include "Time.h"
typedef long RendErr;

class RenderFront 
{
public:
  RendErr GetError(void);
  void Init(void);
  void Shutdown(void);
  void Update(void);


  void Draw(std::vector<SDL_Vertex> const& mesh) const;
  void SetMatrix(glm::mat4x4 const& matrix);
  void SetTranslation(glm::vec2 pos);
  void SetScale(glm::vec2 scale);
  void SetRotation(float rotation);
#ifdef _DEBUG
  SDL_Renderer* GetRenderer(void) { return renderer; };
  SDL_Window* GetWindow(void) { return window; };
#endif
private:
  int Width = 1280;
  int Height = 720;
  int TargetFrameRate = 120;
  long long frameRateMillis = 0;
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Rect ViewPort;
  glm::mat3x3 renderMatrix;
  
};