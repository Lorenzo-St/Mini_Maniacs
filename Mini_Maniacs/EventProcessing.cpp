#include "SDL.h"
#include "Backend.h"

void ProcessEvent(SDL_Event& event) 
{
  //std::cout << "Event: " << static_cast<int>(event.type) << std::endl;

  switch (event.type) 
  {
  case SDL_KEYDOWN:
  case SDL_KEYUP:
  case SDL_CONTROLLERBUTTONDOWN:
  case SDL_CONTROLLERBUTTONUP:
  case SDL_TEXTINPUT:
    InputSystem::inputEvent(event);
    break;
  case SDL_MOUSEMOTION:
  case SDL_MOUSEBUTTONDOWN:
  case SDL_MOUSEBUTTONUP:
  case SDL_MOUSEWHEEL:
    InputSystem::MouseEvent(event);
  
  }
}