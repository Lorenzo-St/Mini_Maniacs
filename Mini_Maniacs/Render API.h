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
  void SetMatrix(glm::mat3x3 const& matrix);
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
  glm::mat3x3 renderMatrix = glm::mat3x3(1.0f);
  glm::mat3x3 projectToSDLSpace(void) const;
};