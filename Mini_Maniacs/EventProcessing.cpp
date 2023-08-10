#include "SDL.h"
#include "Backend.h"

void ProcessEvent(SDL_Event& event) 
{
  switch (event.type) 
  {
  case SDL_KEYDOWN:
  case SDL_KEYUP:
  case SDL_CONTROLLERBUTTONDOWN:
  case SDL_CONTROLLERBUTTONUP:
    InputSystem::inputEvent(event);
    break;
  
  }
}