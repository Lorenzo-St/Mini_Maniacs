#include <iostream>
#include <chrono>
#include <thread>
#include "SDL.h"
#include "Backend.h"
#include "../GLM/ext/matrix_transform.hpp"
#include "../GLM/ext/matrix_clip_space.hpp"
#include "InputSystem.h"

RenderFront api;


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

  frameRateMillis = (1.0f / TargetFrameRate) * 1000;
#if _DEBUG && 0
  std::cout << frameRateMillis << std::endl;
#endif
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
  SDL_RenderPresent(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_RenderClear(renderer);
  Timer last = timeMarker;
  timeMarker = Timer::clock::now();
  std::chrono::duration<double, std::milli> delta = timeMarker - last;
  if (delta.count() < frameRateMillis)
  {
    std::chrono::duration<double, std::milli> delta_ms(frameRateMillis - delta.count());
    auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
#if _DEBUG && 0
    std::cout << "Start Time: "
      << last.time_since_epoch().count()
      << ", End Time: "
      << timeMarker.time_since_epoch().count()
      << ", Duration: "
      << delta.count()
      << " delta_ms: "
      << delta_ms_duration.count()
      << std::endl;
#endif
    Time.deltaTime(frameRateMillis / 1000.0f);
    std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
  }


  timeMarker = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> sleep_time = timeMarker - last;
#if _DEBUG && 0
  std::cout << "Time: " << (delta + sleep_time).count() << std::endl;
#endif
  Input.Update();
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
  const glm::mat4x4 proj = glm::ortho<float>(-Width * 1.0f, Width * 1.0f, -Height * 1.0f, Height * 1.0f);
  std::vector<SDL_Vertex> temp = mesh;
  for (auto& vert : temp) 
  {
    glm::vec2 t = glm::vec2(glm::vec4(convert(vert.position), 0, 1) * projection * proj);
    glm::vec2 m = (t * glm::vec2(Width, -Height)) + glm::vec2(Width / 2.0f + c.pos.x, Height / 2.0f + c.pos.y);
    vert.position = convert(m);
  }
  SDL_RenderGeometry(renderer, nullptr, temp.data(), static_cast<int>(temp.size()), nullptr, 0);
}

void RenderFront::SetMatrix(glm::mat4x4 const& matrix) 
{
  renderMatrix = matrix;
}

void RenderFront::SetMatrixData(glm::vec2 pos, glm::vec2 scale, float rotation) 
{
  glm::mat4x4 mat = glm::identity<glm::mat4x4>();
  mat = glm::translate(mat, glm::vec3(pos, 1));
  mat = glm::scale(mat, glm::vec3( scale, 0 ));
  mat = glm::rotate(mat, rotation, { 0,0,1 });
  mat = glm::transpose(mat);
  renderMatrix = mat;
}

