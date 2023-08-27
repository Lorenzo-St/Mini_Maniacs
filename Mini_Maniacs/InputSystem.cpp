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
  instance->wheelX = 0;
  instance->wheelY = 0;
  instance->activeAny.pressed = false;
  instance->activeAny.triggered = false;

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

SDL_Keycode InputSystem::isPressedAny(void) 
{
  if (instance->activeAny.triggered)
    return instance->activeAny.pressedKey.key;
}

SDL_Keycode InputSystem::isTriggeredAny(void) 
{
  if (instance->activeAny.pressed)
    return instance->activeAny.pressedKey.key;
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
    instance->activeAny.pressedKey.key = event.key.keysym.sym;
    (instance->activeAny.pressed == false) ? instance->activeAny.triggered = true : 0;
    instance->activeAny.pressed = true;

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
  case SDL_TEXTINPUT:
    for (auto& binding : instance->bindings)
    {
      if (binding.binding.key == event.text.text[0])
      {
        (binding.pressed == false) ? binding.triggered = true : 0;
        binding.pressed = true;
#if _DEBUG && 0
        std::cout << "Pressed: " << static_cast<char>(event.key.keysym.scancode) << std::endl;
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
    case SDL_MOUSEWHEEL:
      instance->wheelX = event.wheel.preciseX / std::abs(event.wheel.preciseX);
      instance->wheelY = event.wheel.preciseY / std::abs(event.wheel.preciseY);

      break;
  }
}

