#include "SDL.h"
#include "Render API.h"
#include <iostream>
#include <chrono>

RendErr errorState = 0;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> Time;

Time timeMarker = Time();

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
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == nullptr) 
  {
    errorState = 102;
    return;
  }
  SDL_Rect rect = { 0, 0, Width, Height };
  errorState = SDL_RenderSetViewport(renderer, &rect);
  errorState = SDL_RenderSetScale(renderer, float(Width), float(Height));

  frameRateMillis = long long((1.0f / TargetFrameRate) * 100000);
  timeMarker = Time::clock::now();
}

void RenderFront::Shutdown(void) 
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void RenderFront::Update(void) 
{
  Time last = timeMarker;
  timeMarker = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::duration delta = timeMarker - last;
#ifdef _DEBUG
  std::cout << "Start Time: " 
            << last.time_since_epoch().count() 
            << ", End Time: " 
            << timeMarker.time_since_epoch().count() 
            << ", Duration: " 
            << delta.count() 
            << std::endl;
#endif
  SDL_Delay(frameRateMillis - delta.count());

  SDL_RenderPresent(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderClear(renderer);
}


void RenderFront::Draw(std::vector<SDL_Vertex> const& mesh) 
{

}

void RenderFront::SetMatrix(glm::mat4x4 const& matrix) 
{

}

void RenderFront::SetTranslation(glm::vec2 pos) 
{

}

void RenderFront::SetScale(glm::vec2 scale) 
{

}

void RenderFront::SetRotation(float rotation) 
{

}


