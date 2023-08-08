#pragma once
#include "SDL.h"
#include "glm.hpp"
#include <vector>
#include "Time.h"
typedef long RendErr;
typedef struct Texture Texture;
class mesh;

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
  void DrawRect(glm::vec2 pos, glm::vec2 scale) const;
  void DrawEllipse(glm::vec2 pos, float rad) const;
  void SetMatrix(glm::mat4x4 const& matrix);
  void SetMatrixData(glm::vec2 pos, glm::vec2 scale, float rotation);
  void SetTexture(Texture const* texture);

  void SetColor(SDL_Color c) {  ActiveColor = c; }

  void setZoom(float z) { zoom = z; };

  // Create mesh for drawing
  mesh* CreateMesh(void);
  

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
  float zoom = 1.0f;
  Camera c = { {0,0} };
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Rect ViewPort = {0};
  Texture const* activeTexture = nullptr;
  SDL_Color ActiveColor;
  glm::mat4x4 renderMatrix = glm::mat4x4(1.0f);
};


extern RenderFront api;