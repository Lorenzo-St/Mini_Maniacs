#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include "SDL.h"
#include "Backend.h"
#include "../GLM/ext/matrix_transform.hpp"
#include "../GLM/ext/matrix_clip_space.hpp"
RenderFront api;


static RendErr errorState = 0;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> Timer;

Timer timeMarker = Timer();

RendErr RenderFront::GetError(void)
{
  return errorState;
}

// The function to initialize the render backend.
// 
// After calling this, Make sure to check GetError() for error state
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

  window = SDL_CreateWindow(PROJECT_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);
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
  Textures.SetRenderer(renderer);
}

void RenderFront::Shutdown(void) 
{
  Textures.DropAll();
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
  const glm::mat4x4 projection = renderMatrix/*glm::scale(renderMatrix, glm::vec3(zoom, zoom, 0))*/;
  const glm::mat4x4 proj = glm::ortho<float>(-Width * 1.0f, Width * 1.0f, -Height * 1.0f, Height * 1.0f);
  std::vector<SDL_Vertex> temp = mesh;
  for (auto& vert : temp) 
  {
    glm::vec2 t = glm::vec2(glm::vec4(convert(vert.position), 0, 1) * projection * proj) * zoom;
    glm::vec2 m = (t * glm::vec2(Width, -Height)) + glm::vec2(Width / 2.0f + c.pos.x, Height / 2.0f + c.pos.y);
    vert.position = convert(m);
  }
  SDL_RenderGeometry(renderer, activeTexture, temp.data(), static_cast<int>(temp.size()), nullptr, 0);
  //for (auto& v : temp)
  //  std::cout << v.position.x << "," << v.position.y << std::endl;
  //activeTexture = nullptr;
}

void RenderFront::DrawRect(glm::vec2 pos, glm::vec2 scale) const
{
  std::array<SDL_Vertex, 6> rect = {};
  const glm::mat4x4 proj = glm::ortho<float>(-Width * 1.0f, Width * 1.0f, -Height * 1.0f, Height * 1.0f);

  rect[0].position = { pos.x - scale.x / 2.0f, pos.y - scale.y / 2.0f };
  rect[1].position = { pos.x - scale.x / 2.0f, pos.y + scale.y / 2.0f };
  rect[2].position = { pos.x + scale.x / 2.0f, pos.y + scale.y / 2.0f };
  rect[3].position = { pos.x + scale.x / 2.0f, pos.y + scale.y / 2.0f };
  rect[4].position = { pos.x + scale.x / 2.0f, pos.y - scale.y / 2.0f };
  rect[5].position = { pos.x - scale.x / 2.0f, pos.y - scale.y / 2.0f };
  for (auto& vert : rect) 
  {
    glm::vec2 t = glm::vec2(glm::vec4(convert(vert.position), 0, 1) * proj) * zoom;
    glm::vec2 m = (t * glm::vec2(Width, -Height)) + glm::vec2(Width / 2.0f + c.pos.x, Height / 2.0f + c.pos.y);
    vert.position = convert(m);
  }
  SDL_RenderGeometry(renderer, activeTexture, rect.data(), static_cast<int>(rect.size()), nullptr, 0);

}

void RenderFront::DrawEllipse(glm::vec2 pos, float rad) const
{
  const glm::mat4x4 proj = glm::ortho<float>(-Width * 1.0f, Width * 1.0f, -Height * 1.0f, Height * 1.0f);
  std::vector<SDL_Vertex> ellip = {};
  rad *= rad;
  SDL_FPoint cen = convert(pos);
  for (float angle = 0, i = 0; angle < 360; angle += 15, i+=3) 
  {
    ellip.push_back({});
    ellip.push_back({});
    ellip.push_back({});
    ellip[i  ].position.x = (pos.x + rad * std::sinf((M_PI * angle) / 180));
    ellip[i  ].position.y = (pos.y + rad * std::cosf((M_PI * angle) / 180));
    ellip[i+1].position.x = (pos.x);
    ellip[i+1].position.y = (pos.y);
    ellip[i+2].position.x = (pos.x + rad * std::sinf((M_PI * (angle + 15)) / 180));
    ellip[i+2].position.y = (pos.y + rad * std::cosf((M_PI * (angle + 15)) / 180));
    ellip[i  ].position = convert(glm::vec2(glm::vec4(convert(ellip[i  ].position), 0,1) * proj * zoom));
    ellip[i  ].position = convert(convert(ellip[i  ].position) * glm::vec2(Width, -Height) + glm::vec2(Width / 2.0f + c.pos.x, Height / 2.0f + c.pos.y));
    ellip[i+1].position = convert(glm::vec2(glm::vec4(convert(ellip[i+1].position), 0, 1) * proj * zoom));
    ellip[i+1].position = convert(convert(ellip[i+1].position) * glm::vec2(Width, -Height) + glm::vec2(Width / 2.0f + c.pos.x, Height / 2.0f + c.pos.y));
    ellip[i+2].position = convert(glm::vec2(glm::vec4(convert(ellip[i+2].position), 0, 1) * proj * zoom));
    ellip[i+2].position = convert(convert(ellip[i+2].position) * glm::vec2(Width, -Height) + glm::vec2(Width / 2.0f + c.pos.x, Height / 2.0f + c.pos.y));
  }

  SDL_RenderGeometry(renderer, activeTexture, ellip.data(), static_cast<int>(ellip.size()), nullptr, 0);

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

void RenderFront::SetTexture(Texture texture)
{
  activeTexture = texture;
}

mesh* RenderFront::CreateMesh(void) 
{ 
  return new mesh(); 
}

