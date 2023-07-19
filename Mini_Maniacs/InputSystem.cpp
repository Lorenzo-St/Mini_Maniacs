#include "InputSystem.h"

void InputSystem::Update(void)
{
  for (auto& binding : bindings)
  {
    binding.triggered = false;
    binding.pressed = false;
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


