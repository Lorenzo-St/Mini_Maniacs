#include "SDL.h"
#include "Backend.h"

void ProcessEvent(SDL_Event& event) 
{
  std::cout << "Event: " << static_cast<char>(event.type) << std::endl;

  switch (event.type) 
  {
  case SDL_KEYDOWN:
  case SDL_KEYUP:
  case SDL_CONTROLLERBUTTONDOWN:
  case SDL_CONTROLLERBUTTONUP:

    InputSystem::inputEvent(event);
    break;
  case SDL_MOUSEMOTION:
  case SDL_MOUSEBUTTONDOWN:
  case SDL_MOUSEBUTTONUP:
    InputSystem::MouseEvent(event);
  
  }
}