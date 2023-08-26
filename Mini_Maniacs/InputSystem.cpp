#include "InputSystem.h"
#if _DEBUG
#include <iostream>
#include <string>
#endif


InputSystem* InputSystem::GetInstance()
{
  if (instance == nullptr)
    instance = new InputSystem();
  return instance;
}

void InputSystem::Update(void)
{
  if (instance == nullptr)
    instance = new InputSystem();
  for (auto& binding : instance->bindings)
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
  if (instance == nullptr)
    instance = new InputSystem();
  for (auto& binding : instance->bindings)
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
  if (instance == nullptr)
    instance = new InputSystem();
  for (auto& binding : instance->bindings)
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
  if (instance == nullptr)
    instance = new InputSystem();
  instance->bindings.push_back(Binding(a, b, type));
}
void InputSystem::addBinding(Action a, input b)
{
  if (instance == nullptr)
    instance = new InputSystem();
  instance->bindings.push_back(Binding(a, b));
}

void InputSystem::inputEvent(SDL_Event event) 
{
  if (instance == nullptr)
    instance = new InputSystem();

  switch (event.type)
  {
  case SDL_KEYDOWN:
    for (auto& binding : instance->bindings)
    {
      if (binding.binding.key == event.key.keysym.sym)
      {
        (binding.pressed == false) ? binding.triggered = true : 0;
        binding.pressed = true;
#if _DEBUG && 0
        std::cout << "Pressed: " << static_cast<char>(event.key.keysym.sym) << std::endl;
#endif
      }
    }
    break;
  case SDL_KEYUP:
    for (auto& binding : instance->bindings)
    {
      if (binding.binding.key == event.key.keysym.sym)
      {  
        binding.pressed = false;
#if _DEBUG && 0
        std::cout << "Released: " << static_cast<char>(event.key.keysym.sym) << std::endl;
#endif
      }

    }
    break;

  }

}


void InputSystem::MouseEvent(SDL_Event event) 
{
  if (instance == nullptr)
    instance = new InputSystem();

  switch (event.type) 
  {
    case SDL_MOUSEMOTION:
      instance->mouseX = event.motion.x;
      instance->mouseY = event.motion.y;

    break;
    case SDL_MOUSEBUTTONDOWN:
      if (event.button.button == 1)
        instance->LMouseDown = true;
      else if (event.button.button == 3)
        instance->RMouseDown = true;

#if _DEBUG && 0
      std::cout << "Pressed: " << static_cast<int>(event.button.button) << std::endl;
#endif
      break;
    case SDL_MOUSEBUTTONUP:
      if (event.button.button == 1)
        instance->LMouseDown = false;
      else if (event.button.button == 3)
        instance->RMouseDown = false;
#if _DEBUG && 0
      std::cout << "Released: " << static_cast<int>(event.button.button) << std::endl;
#endif
      break;
  }
}

