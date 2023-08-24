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
  if (TTF_Init() != 0) throw std::runtime_error("What?");

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
  SDL_SetRenderDrawColor(renderer, ClearColor.r, ClearColor.g, ClearColor.b, ClearColor.a);
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
  InputSystem::Update();
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
  std::vector<SDL_Vertex> temp = mesh;
  for (auto& vert : temp) 
  {
    vert.position = convert((ConvertToScreenSpace(glm::vec4((convert(vert.position)) , 0 , 1) * renderMatrix)));
    vert.tex_coord = convert(glm::vec4(convert(vert.tex_coord), 0, 1) * UVmatrix);
  }
  if(activeTexture)
    SDL_RenderGeometry(renderer, const_cast<Texture*>(activeTexture)->texture(), temp.data(), static_cast<int>(temp.size()), nullptr, 0);
  else
    SDL_RenderGeometry(renderer, nullptr, temp.data(), static_cast<int>(temp.size()), nullptr, 0);

  //for (auto& v : temp)
  //  std::cout << v.position.x << "," << v.position.y << std::endl;
  //activeTexture = nullptr;

  
}

glm::vec2 RenderFront::ConvertToWorldSpace(glm::vec2 const& cl) const
{
  return  glm::vec2((cl.x) - Width / 2.0f, -(cl.y) + Height / 2.0f) / zoom;
}

glm::vec2 RenderFront::ConvertToScreenSpace(glm::vec2 const& cl) const
{
  return  glm::vec2((cl.x) * zoom + Width / 2.0f, -(cl.y) * zoom + Height / 2.0f);
}


void RenderFront::DrawRect(glm::vec2 pos, glm::vec2 scale) const
{
  std::array<SDL_Vertex, 6> rect = {};

  rect[0].position = { pos.x - scale.x / 2.0f, pos.y - scale.y / 2.0f };
  rect[1].position = { pos.x - scale.x / 2.0f, pos.y + scale.y / 2.0f };
  rect[2].position = { pos.x + scale.x / 2.0f, pos.y + scale.y / 2.0f };
  rect[3].position = { pos.x + scale.x / 2.0f, pos.y + scale.y / 2.0f };
  rect[4].position = { pos.x + scale.x / 2.0f, pos.y - scale.y / 2.0f };
  rect[5].position = { pos.x - scale.x / 2.0f, pos.y - scale.y / 2.0f };
  for (auto& vert : rect) 
  {

    vert.position = convert(ConvertToScreenSpace(convert(vert.position)));
  }
  for (auto& a : rect)
  {
    a.color = ActiveColor;
  }
  SDL_RenderGeometry(renderer, nullptr, rect.data(), static_cast<int>(rect.size()), nullptr, 0);

}

void RenderFront::DrawEllipse(glm::vec2 pos, float rad) const
{
  const glm::mat4x4 proj = glm::ortho<float>(-Width * 1.0f, Width * 1.0f, -Height * 1.0f, Height * 1.0f);
  std::vector<SDL_Vertex> ellip = {};
  SDL_FPoint cen = convert(pos);
  for (float angle = 0, p = 0; angle < 360; angle += 15, p+=3) 
  {
    int i = static_cast<int>(p);
    ellip.push_back({});
    ellip.push_back({});
    ellip.push_back({});
    ellip[i  ].position.x = (pos.x + rad * std::sinf((3.14159f * angle) / 180.0f));
    ellip[i  ].position.y = (pos.y + rad * std::cosf((3.14159f * angle) / 180.0f));
    ellip[i+1].position.x = (pos.x);
    ellip[i+1].position.y = (pos.y);
    ellip[i+2].position.x = (pos.x + rad * std::sinf((3.14159f * (angle + 15.0f)) / 180.0f));
    ellip[i+2].position.y = (pos.y + rad * std::cosf((3.14159f * (angle + 15.0f)) / 180.0f));
    ellip[i  ].position = convert(glm::vec2(glm::vec4(convert(ellip[i  ].position), 0,1) * proj * zoom));
    ellip[i  ].position = convert(convert(ellip[i  ].position) * glm::vec2(Width, -Height) + glm::vec2(Width / 2.0f + c.pos.x, Height / 2.0f + c.pos.y));
    ellip[i+1].position = convert(glm::vec2(glm::vec4(convert(ellip[i+1].position), 0, 1) * proj * zoom));
    ellip[i+1].position = convert(convert(ellip[i+1].position) * glm::vec2(Width, -Height) + glm::vec2(Width / 2.0f + c.pos.x, Height / 2.0f + c.pos.y));
    ellip[i+2].position = convert(glm::vec2(glm::vec4(convert(ellip[i+2].position), 0, 1) * proj * zoom));
    ellip[i+2].position = convert(convert(ellip[i+2].position) * glm::vec2(Width, -Height) + glm::vec2(Width / 2.0f + c.pos.x, Height / 2.0f + c.pos.y));
  }
  for (auto& a : ellip) 
  {
    a.color = ActiveColor;
  }
  SDL_RenderGeometry(renderer, nullptr, ellip.data(), static_cast<int>(ellip.size()), nullptr, 0);

}



void RenderFront::SetMatrix(glm::mat4x4 const& matrix) 
{
  renderMatrix = matrix;
}

void RenderFront::SetMatrixData(glm::vec2 pos, glm::vec2 scale, float rotation) 
{
  glm::mat4x4 mat = glm::identity<glm::mat4x4>();
  mat = glm::translate(mat, glm::vec3(pos + glm::vec2(c.pos.x, -c.pos.y), 1));
  mat = glm::scale(mat, glm::vec3( scale, 0 ));
  mat = glm::rotate(mat, rotation, { 0,0,1 });
  mat = glm::transpose(mat);
  renderMatrix = mat;
}

void RenderFront::MoveMatrixData(glm::vec2 pos, glm::vec2 scale, float rotation)
{
  glm::mat4x4 mat = glm::identity<glm::mat4x4>();
  mat = glm::translate(mat, glm::vec3(pos, 1));
  mat = glm::scale(mat, glm::vec3(scale, 0));
  mat = glm::rotate(mat, rotation, { 0,0,1 });
  mat = glm::transpose(mat);
  renderMatrix *= mat;
}


void RenderFront::SetTexture(Texture const* texture) 
{
  activeTexture = texture;
}

mesh* RenderFront::CreateMesh(void) 
{ 
  return new mesh(); 
}

void RenderFront::DrawText(const char* text, glm::vec2 pos, int size) 
{
  if (activeFont == nullptr)
    throw std::runtime_error("Hello?? There is no font");

  TTF_SetFontSize(activeFont->font, size);
  SDL_Rect rect = { static_cast<int>(pos.x), static_cast<int>(pos.y) };
  TTF_SizeText(activeFont->font, text, &rect.w, &rect.h);
  SDL_Surface* surface = TTF_RenderText_Solid(activeFont->font, text, ActiveColor);

  SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_RenderCopy(renderer, message, nullptr, &rect);
}

void RenderFront::LoadFont(const char* path) 
{
  FontInfo* f = Fonts::FetchFont(path);
  if (f == nullptr)
  {
    f = Fonts::LoadFont(path);
  }
  activeFont = f;
}

