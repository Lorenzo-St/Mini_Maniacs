#include "SDL.h"
#include "Render API.h"
#include <iostream>
#include <chrono>
#include "Time.h"
#include "../GLM/ext/matrix_transform.hpp"
#include "../GLM/ext/matrix_clip_space.hpp"
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
  const glm::mat4x4 projection = renderMatrix;
  std::vector<SDL_Vertex> temp = mesh;
  for (auto& vert : temp) 
  {
    glm::vec2 t = convert(vert.position) * glm::vec2(Width, -Height) + glm::vec2(Width/2.0f, Height/2.0f);
    glm::vec3 m = projection * glm::vec4(t, 0,1);
    vert.position = convert(glm::vec2(m));
  }
  SDL_RenderGeometry(renderer, nullptr, temp.data(), temp.size(), nullptr, 0);
}

void RenderFront::SetMatrix(glm::mat4x4 const& matrix) 
{
  renderMatrix = matrix;
}

void RenderFront::SetTranslation(glm::vec2 pos) 
{
  //pos += glm::vec2(Width / 2.0f, Height / 2.0f);
  renderMatrix = glm::translate(renderMatrix, glm::vec3(pos, 0));
}

void RenderFront::SetScale(glm::vec2 scale) 
{
  renderMatrix = glm::scale(renderMatrix, glm::vec3(scale,1));
}

void RenderFront::SetRotation(float rotation) 
{
  renderMatrix = glm::rotate(renderMatrix, rotation, glm::vec3(0,0,1));
}


