#include "SDL.h"
#include "Render API.h"
#include <iostream>
#include <chrono>
#include "Time.h"
#include "../GLM/gtx/matrix_transform_2d.hpp"
RendErr errorState = 0;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> Timer;

Timer timeMarker = Timer();

RendErr RenderFront::GetError(void)
{
  return errorState;
}

// The function to initialize the render backend.
// 
// After call, Make sure to check GetError() for error state
//  If error state is not 0, then error has occured and 
//  Interface is not initialized
//
void RenderFront::Init(void) 
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "Initilization failed" << SDL_GetError() << std::endl;
    errorState = 100;
    return;
  }

  window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);
  if (window == nullptr)
  {
    errorState = 101;
    return;
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
  if (renderer == nullptr) 
  {
    errorState = 102;
    return;
  }
  SDL_Rect rect = { 0, 0, Width, Height };
  errorState = SDL_RenderSetViewport(renderer, &rect);

  frameRateMillis = long long((1.0f / TargetFrameRate) * 10000);
  std::cout << frameRateMillis << std::endl;
  timeMarker = Timer::clock::now();
}

void RenderFront::Shutdown(void) 
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void RenderFront::Update(void) 
{
  Timer last = timeMarker;
  timeMarker = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::duration delta = timeMarker - last;
  long long sleep_duration = frameRateMillis - std::chrono::duration_cast<std::chrono::microseconds>(delta).count();
#if _DEBUG && 0
  std::cout << "Start Time: " 
            << last.time_since_epoch().count() 
            << ", End Time: " 
            << timeMarker.time_since_epoch().count() 
            << ", Duration: " 
            << delta.count() 
            << ", Sleeping for: " 
            << sleep_duration
            << std::endl;
#endif
  if (sleep_duration < 0)
    sleep_duration = 0;
  Time.deltaTime(static_cast<float>(frameRateMillis)/ 10000.0f);
  SDL_Delay(static_cast<Uint32>(sleep_duration));

  SDL_RenderPresent(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_RenderClear(renderer);
  timeMarker = std::chrono::high_resolution_clock::now();

}

glm::mat3x3 RenderFront::projectToSDLSpace(void) const
{
  glm::ivec2 winSize;
  SDL_GetWindowSize(window, &winSize.x, &winSize.y);
  const glm::vec2 winSizeHalf = glm::vec2(winSize) / 2.f;
  glm::mat3x3 mat(1.0f);
  mat = glm::translate(mat, winSizeHalf) * glm::scale(mat, { winSizeHalf.x, winSizeHalf.y });
  return mat;
}

inline glm::vec2 convert(SDL_FPoint f) 
{
  return { f.x, f.y };
}

inline SDL_FPoint convert(glm::vec2 f)
{
  return { f.x, f.y };
}

void RenderFront::Draw(std::vector<SDL_Vertex> const& mesh) const
{
  const glm::mat3x3 projection = renderMatrix * projectToSDLSpace();
  std::vector<SDL_Vertex> temp = mesh;
  for (auto& vert : temp) 
  {
    vert.position = convert(glm::vec2(glm::vec3( convert(vert.position), 1 ) * projection));
  }
  SDL_RenderGeometry(renderer, nullptr, temp.data(), temp.size(), nullptr, 0);
}

void RenderFront::SetMatrix(glm::mat3x3 const& matrix) 
{
  renderMatrix = matrix;
}

void RenderFront::SetTranslation(glm::vec2 pos) 
{
  renderMatrix = glm::translate(renderMatrix, pos);
}

void RenderFront::SetScale(glm::vec2 scale) 
{
  renderMatrix = glm::scale(renderMatrix, scale);
}

void RenderFront::SetRotation(float rotation) 
{
  renderMatrix = glm::rotate(renderMatrix, rotation);
}


