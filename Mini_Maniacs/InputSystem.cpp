#include "InputSystem.h"
#if _DEBUG
#include <iostream>
#endif
InputSystem Input;

void InputSystem::Update(void)
{
  for (auto& binding : bindings)
  {
#if _DEBUG && 0
    std::cout << "Key : " 
      << binding.binding.key 
      << " Pressed : " 
      << binding.pressed 
      << " Triggered : "
      << binding.triggered
      << std::endl;
#endif
    binding.triggered = false;
  }
}

bool InputSystem::isPressed(Action a) 
{
  for (auto& binding : bindings) 
  {
    if (binding.action == a && binding.pressed) 
    {
      return true;
    }
  }
  return false;
}

bool InputSystem::isTriggered(Action a) 
{
  for (auto& binding : bindings)
  {
    if (binding.action == a && binding.triggered)
    {
      return true;
    }
  }
  return false;
}

void InputSystem::addBinding(Action a, char type, input b)
{
  bindings.push_back(Binding(a, b, type));
}
void InputSystem::addBinding(Action a, input b)
{
  bindings.push_back(Binding(a, b));
}

void InputSystem::inputEvent(SDL_Event event) 
{
  switch (event.type)
  {
  case SDL_KEYDOWN:
    for (auto& binding : bindings)
    {
      if (binding.binding.key == event.key.keysym.sym)
      {
        (binding.pressed == false) ? binding.triggered = true : 0;
        binding.pressed = true;
      }
    }
    break;
  case SDL_KEYUP:
    for (auto& binding : bindings)
    {
      if (binding.binding.key == event.key.keysym.sym)
        binding.pressed = false;
    }
    break;
  
  }

}



